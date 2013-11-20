#pragma once

#include "Hect.h"

#include <btBulletDynamicsCommon.h>

namespace hect
{

btVector3 convertToBullet(const Vector3<>& v);
btQuaternion convertToBullet(const Quaternion<>& q);
btTransform convertToBullet(const Transform& t);

}