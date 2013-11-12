#include "StarField.h"

StarField::Node::Node(StarField* starField, const Vector3<>& position, double size, unsigned depth) :
    starField(starField),
    transform(position),
    area(position - size / 2.0, position + size / 2.0),
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

void StarField::renderDebug(Camera& camera, DebugRenderingSystem& renderingSystem)
{
    Vector3<> scale = _node.area.maximum() - _node.area.minimum();
    Vector4<> color = Vector4<>(1.0, 0.0, 0.0, 1.0);
    renderingSystem.renderWireframeBox(_node.transform.position(), scale, color);
}
