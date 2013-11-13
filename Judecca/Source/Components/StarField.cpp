#include "StarField.h"

StarField::Node::Node(StarField* starField, const Vector3<>& position, double size, unsigned depth) :
    starField(starField),
    transform(position),
    area(position - size / 2.0, position + size / 2.0),
    size(size),
    depth(depth)
{
}

StarField::StarField(const Vector3<>& position, double size, unsigned maxDepth, DensitySampler::Ref densitySampler, Material::Ref material) :
    _maxDepth(maxDepth),
    _densitySampler(densitySampler),
    _material(material),
    _node(this, position, size, 0)
{
}

void StarField::render(const Camera& camera, RenderingSystem& renderingSystem)
{
    _updateNode(_node, camera);
    _renderNode(_node, camera, renderingSystem, true);
}

void StarField::renderDebug(const Camera& camera, DebugRenderingSystem& renderingSystem)
{
    _renderNodeDebug(_node, camera, renderingSystem, true);
}

void StarField::_updateNode(Node& node, const Camera& camera)
{
    if (node.depth < _maxDepth)
    {
        double distance = (camera.position() - node.transform.position()).length();
        double splitThreshold = node.size * 2.0;

        // Split the node if it is close enough
        if (distance <= splitThreshold && node.children.empty())
        {
            _splitNode(node);
        }

        // Colapse the node if it is far enough
        else if (distance > splitThreshold && !node.children.empty())
        {
            node.children.clear();
        }
    }

    // Recurse through children
    for (Node& child : node.children)
    {
        _updateNode(child, camera);
    }
}

void StarField::_renderNode(Node& node, const Camera& camera, RenderingSystem& renderingSystem, bool frustumTest)
{
    if (frustumTest)
    {
        Frustum<>::TestResult result = camera.frustum().testAxisAlignedBox(node.area);
        if (result == Frustum<>::Outside)
        {
            // Completely outside of view
            return;
        }
        else if (result == Frustum<>::Inside)
        {
            // Entirely in view, no need to check against frustum anymore because
            // all children will also be entirely in frustum
            frustumTest = false; 
        }
    }

    if (node.depth < _maxDepth)
    {
        double distance = (camera.position() - node.transform.position()).length();
        double splitThreshold = node.size * 2.0;

        // Split the node if it is close enough
        if (distance <= splitThreshold && node.children.empty())
        {
            _splitNode(node);
        }

        // Colapse the node if it is far enough
        else if (distance > splitThreshold && !node.children.empty())
        {
            node.children.clear();
        }
    }

    // Generate the star mesh if we need to
    if (!node.mesh)
    {
        _generateMesh(node);
    }

    // Render the star mesh
    if (node.mesh->vertexCount() > 0 && node.mesh->indexCount() > 0)
    {
        renderingSystem.renderMesh(*node.mesh, *_material, node.transform);
    }

    // Recurse through children
    for (Node& child : node.children)
    {
        _renderNode(child, camera, renderingSystem, frustumTest);
    }
}

void StarField::_renderNodeDebug(Node& node, const Camera& camera, DebugRenderingSystem& renderingSystem, bool frustumTest)
{
    if (frustumTest)
    {
        Frustum<>::TestResult result = camera.frustum().testAxisAlignedBox(node.area);
        if (result == Frustum<>::Outside)
        {
            // Completely outside of view
            return;
        }
        else if (result == Frustum<>::Inside)
        {
            // Entirely in view, no need to check against frustum anymore because
            // all children will also be entirely in frustum
            frustumTest = false; 
        }
    }

    Vector3<> scale(node.size);
    Vector4<> color = Vector4<>(1.0, 1.0, 1.0, 0.125);
    renderingSystem.renderWireframeBox(node.transform.position(), scale, color);

    for (Node& child : node.children)
    {
        _renderNodeDebug(child, camera, renderingSystem, frustumTest);
    }
}

void StarField::_splitNode(Node& node)
{
    Vector3<> position = node.transform.position();
    double halfSize = node.size / 2.0;
    double quarterSize = halfSize / 2.0;

    node.children.clear();
    node.children.reserve(8);
    node.children.push_back(Node(this, position - Vector3<>( 1, -1,  1) * quarterSize, halfSize, node.depth + 1));
    node.children.push_back(Node(this, position - Vector3<>( 1, -1, -1) * quarterSize, halfSize, node.depth + 1));
    node.children.push_back(Node(this, position - Vector3<>( 1,  1,  1) * quarterSize, halfSize, node.depth + 1));
    node.children.push_back(Node(this, position - Vector3<>( 1,  1, -1) * quarterSize, halfSize, node.depth + 1));
    node.children.push_back(Node(this, position - Vector3<>(-1, -1,  1) * quarterSize, halfSize, node.depth + 1));
    node.children.push_back(Node(this, position - Vector3<>(-1, -1, -1) * quarterSize, halfSize, node.depth + 1));
    node.children.push_back(Node(this, position - Vector3<>(-1,  1,  1) * quarterSize, halfSize, node.depth + 1));
    node.children.push_back(Node(this, position - Vector3<>(-1,  1, -1) * quarterSize, halfSize, node.depth + 1));
}

void StarField::_generateMesh(Node& node)
{
    VertexAttribute::Array attributes;
    attributes.reserve(2);
    attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float32, 3));
    attributes.push_back(VertexAttribute(VertexAttribute::Weight0, VertexAttribute::Float32, 1));
    VertexLayout vertexLayout(attributes);

    Mesh::Ref mesh(new Mesh(vertexLayout, Mesh::Points, Mesh::Unsigned32));

    MeshBuilder builder(*mesh);

    Random random(_hashPoint(node.transform.position()));

    const Vector3<>& minimum = node.area.minimum();
    const Vector3<>& maximum = node.area.maximum();

    unsigned pointCount = 100;

    unsigned index = 0;
    for (unsigned i = 0; i < pointCount; ++i)
    {
        Vector3<> position;
        position.x = random.nextDouble(minimum.x, maximum.x);
        position.y = random.nextDouble(minimum.y, maximum.y);
        position.z = random.nextDouble(minimum.z, maximum.z);

        double d = _densitySampler->density(position, 0);
        double p = random.nextDouble(0, 1);
        if (p > d)
        {
            continue;
        }

        builder.addVertex();
        builder.setAttributeData(VertexAttribute::Position, position - node.transform.position());
        builder.setAttributeData(VertexAttribute::Weight0, random.nextFloat(0, 1));
        builder.addIndex(index++);
    }

    node.mesh = mesh;
}

unsigned StarField::_hashPoint(const Vector3<>& point) const
{
    uint32_t x;
    *(float*)&x = (float)point.x;
    
    unsigned y;
    *(float*)&y = (float)point.y;
    
    unsigned z;
    *(float*)&z = (float)point.z;

    return x * 73856093 ^ y * 19349663 ^ z * 83492791;
}