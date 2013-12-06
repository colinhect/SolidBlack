#pragma once

#include "Hect.h"

#ifdef HECT_WINDOWS
#pragma warning(push, 0)
#endif

#include <btBulletDynamicsCommon.h>

#ifdef HECT_WINDOWS
#pragma warning(pop)
#endif

namespace hect
{

btVector3 convertToBullet(const Vector3<>& v);
btQuaternion convertToBullet(const Quaternion<>& q);
btTransform convertToBullet(const Transform& t);
btTriangleMesh* convertToBullet(const Mesh& m);

Vector3<> convertFromBullet(const btVector3& v);
Quaternion<> convertFromBullet(const btQuaternion& q);
Transform convertFromBullet(const btTransform& t);

}