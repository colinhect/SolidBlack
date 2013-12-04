#include "Hect.h"

using namespace hect;

ComponentTypeId BaseComponent::nextTypeId()
{
    static ComponentTypeId nextTypeId = 0;
    return nextTypeId++;
}