#include "Hect.h"

using namespace hect;

ComponentType BaseComponent::nextType()
{
    static ComponentType nextType = 0;
    return nextType++;
}