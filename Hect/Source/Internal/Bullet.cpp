#include "Bullet.h"

namespace hect
{

btVector3 convertToBullet(const Vector3<>& v)
{
    return btVector3(v.x, v.y, v.z);
}

btQuaternion convertToBullet(const Quaternion<>& q)
{
    return btQuaternion(q.x, q.y, q.z, q.w);
}

btTransform convertToBullet(const Transform& t)
{
    btTransform transform;
    transform.setOrigin(convertToBullet(t.position()));
    transform.setRotation(convertToBullet(t.rotation()));
    return transform;
}

}