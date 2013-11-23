#pragma once

namespace hect
{

class Behavior :
    public Component<Behavior>
{
public:
    virtual void preUpdate(double timeStep) { }
    virtual void update(double timeStep) { }
    virtual void postUpdate(double timeStep) { }
};

}