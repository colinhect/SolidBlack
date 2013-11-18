#pragma once

#include <Hect.h>
using namespace hect;

class SolidBlackState :
    public State,
    public Keyboard::Listener
{
public:
    SolidBlackState(Engine& engine, double timeStep);

    virtual void begin();
    virtual void end();

    void notifyKeyboardEvent(const Keyboard::Event& event);

protected:
    unsigned debugLevel() const;

private:
    unsigned _debugLevel;
};