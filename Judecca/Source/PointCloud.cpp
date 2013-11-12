#include "PointCloud.h"

PointCloud::PointCloud(unsigned seed, unsigned pointCount, const AxisAlignedBox<>& area, const DensitySampler& sampler, unsigned channel)
{
    VertexAttribute::Array attributes;
    attributes.reserve(4);
    attributes.push_back(VertexAttribute(VertexAttribute::Position, VertexAttribute::Float32, 3));
    attributes.push_back(VertexAttribute(VertexAttribute::Weight0, VertexAttribute::Float32, 1));
    attributes.push_back(VertexAttribute(VertexAttribute::Weight1, VertexAttribute::Float32, 1));
    attributes.push_back(VertexAttribute(VertexAttribute::Weight2, VertexAttribute::Float32, 1));
    VertexLayout vertexLayout(attributes);

    _mesh = Mesh::Ref(new Mesh(vertexLayout, Mesh::Points, Mesh::Unsigned32));

    MeshBuilder builder(*_mesh);

    Random random(seed);

    const Vector3<>& minimum = area.minimum();
    const Vector3<>& maximum = area.maximum();

    unsigned index = 0;
    for (unsigned i = 0; i < pointCount; ++i)
    {
        Vector3<> position;
        position.x = random.nextDouble(minimum.x, maximum.x);
        position.y = random.nextDouble(minimum.y, maximum.y);
        position.z = random.nextDouble(minimum.z, maximum.z);

        double d = sampler.density(position, channel);
        double p = random.nextDouble(0, 1);
        if (p > d)
        {
            continue;
        }

        builder.addVertex();
        builder.setAttributeData(VertexAttribute::Position, position);
        builder.setAttributeData(VertexAttribute::Weight0, random.nextFloat(0, 1));
        builder.setAttributeData(VertexAttribute::Weight1, random.nextFloat(0, 1));
        builder.setAttributeData(VertexAttribute::Weight2, random.nextFloat(0, 1));
        builder.addIndex(index++);
    }
}

const Mesh::Ref& PointCloud::mesh() const
{
    return _mesh;
}