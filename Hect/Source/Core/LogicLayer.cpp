#include "Hect.h"

using namespace hect;

LogicLayer::LogicLayer() :
    _active(true)
{
}

void LogicLayer::fixedUpdate(double timeStep)
{
    timeStep;
}

void LogicLayer::frameUpdate(double delta)
{
    delta;
}

bool LogicLayer::isActive() const
{
    return _active;
}

void LogicLayer::setActive(bool active)
{
    _active = active;
}