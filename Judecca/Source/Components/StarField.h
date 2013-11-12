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
        unsigned depth;
        //PointCloud pointCloud;
        //std::vector<Node> children;
    };

    StarField(const Vector3<>& position, double size, unsigned maxDepth, DensitySampler::Ref densitySampler, Material::Ref material);

    //void render(Camera& camera, RenderingSystem& renderingSystem);
    void renderDebug(Camera& camera, DebugRenderingSystem& renderingSystem);

private:
    //void _renderNode(Camera& camera, RenderingSystem& renderingSystem, bool cull);

    unsigned _maxDepth;
    DensitySampler::Ref _densitySampler;
    Material::Ref _material;
    Node _node;
};