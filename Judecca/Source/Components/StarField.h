#pragma once

#include "PointCloud.h"

class StarField :
    public Renderable
{
public:
    class Node
    {
    public:
        Node(StarField* starField, const Vector3<>& position, double size, unsigned depth);

        StarField* starField;
        Transform transform;
        AxisAlignedBox<> area;
        double size;
        unsigned depth;
        Mesh::Ref mesh;
        std::vector<Node> children;
    };

    StarField(const Vector3<>& position, double size, unsigned maxDepth, DensitySampler::Ref densitySampler, Material::Ref material);

    void render(const Camera& camera, RenderingSystem& renderingSystem);
    void renderDebug(const Camera& camera, DebugRenderingSystem& renderingSystem);

private:
    void _updateNode(Node& node, const Camera& camera);
    void _renderNode(Node& node, const Camera& camera, RenderingSystem& renderingSystem, bool frustumTest);
    void _renderNodeDebug(Node& node, const Camera& camera, DebugRenderingSystem& renderingSystem, bool frustumTest);

    void _splitNode(Node& node);
    void _generateMesh(Node& node);

    unsigned _hashPoint(const Vector3<>& point) const;

    unsigned _maxDepth;
    DensitySampler::Ref _densitySampler;
    Material::Ref _material;
    Node _node;
};