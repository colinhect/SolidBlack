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

}