#include "Bullet.h"

namespace hect
{

btVector3 convertToBullet(const Vector3<>& v)
{
    return btVector3(v.x, v.y, v.z);
}

btQuaternion convertToBullet(const Quaternion<>& q)
{
    return btQuaternion(q.x, q.y, q.z, -q.w);
}

btTransform convertToBullet(const Transform& t)
{
    btTransform transform;
    transform.setOrigin(convertToBullet(t.position()));
    transform.setRotation(convertToBullet(t.rotation()));
    return transform;
}

btTriangleMesh* convertToBullet(const Mesh& m)
{
    MeshReader meshReader(m);

    std::vector<btVector3> vertices;
    while (meshReader.nextVertex())
    {
        Vector3<float> position = meshReader.readAttributeVector3(VertexAttributeSemantic::Position);
        vertices.push_back(convertToBullet(position));
    }

    std::vector<size_t> indices;
    while (meshReader.nextIndex())
    {
        indices.push_back(meshReader.readIndexInt());
    }

    btTriangleMesh* mesh = new btTriangleMesh();
    for (size_t i = 0; i < indices.size() - 2; i += 3)
    {
        mesh->addTriangle(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
    }

    return mesh;
}

Vector3<> convertFromBullet(const btVector3& v)
{
    return Vector3<>(v.x(), v.y(), v.z());
}

Quaternion<> convertFromBullet(const btQuaternion& q)
{
    return Quaternion<>(q.x(), q.y(), q.z(), -q.w());
}

Transform convertFromBullet(const btTransform& t)
{
    Transform transform;
    transform.setPosition(convertFromBullet(t.getOrigin()));
    transform.setRotation(convertFromBullet(t.getRotation()));
    return transform;
}

}