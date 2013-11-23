#pragma once

namespace hect
{

class BehaviorSystem :
    public System
{
public:
    BehaviorSystem();

    void update(double timeStep);
};

}