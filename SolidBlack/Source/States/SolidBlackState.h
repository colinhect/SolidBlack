#pragma once

#include <Hect.h>
using namespace hect;

class SolidBlackState :
    public State,
    public KeyboardListener
{
public:
    SolidBlackState(Engine& engine, double timeStep);

    virtual void begin();
    virtual void end();

    void receiveKeyboardEvent(const KeyboardEvent& event);

protected:
    unsigned debugLevel() const;

private:
    unsigned _debugLevel;
};