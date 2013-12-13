#include "SolidBlack.h"

Bubble::Bubble(AssetCache& assetCache)
{
    _scene.addSystem(_physicsSystem);

    DataValue::Ref testRigidBodyValue = assetCache.get<DataValue>("Testing/TestRigidBody.entity");
    _testRigidBody = _scene.createEntity();
    _testRigidBody.load(*testRigidBodyValue, assetCache);
}

Bubble::~Bubble()
{
}

void Bubble::update(double timeStep)
{
    _physicsSystem.update(timeStep, 1);
    _scene.refresh();
}