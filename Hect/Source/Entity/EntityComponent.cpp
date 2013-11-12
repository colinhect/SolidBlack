#include "Hect.h"

using namespace hect;

EntityComponentType BaseComponent::nextType()
{
    static EntityComponentType nextType = 0;
    return nextType++;
}