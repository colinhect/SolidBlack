#include "SolidBlackState.h"

SolidBlackState::SolidBlackState(Engine& engine, double timeStep) :
    State(engine, timeStep),
    _debugLevel(0)
{
    // Create the input axes
    InputAxis viewX("ViewX", InputAxis::MouseMoveX);
    viewX.setAcceleration(0.0025);
    viewX.setGravity(10);

    InputAxis viewY("ViewY", InputAxis::MouseMoveY);
    viewY.setAcceleration(0.0025);
    viewY.setGravity(10);

    InputAxis moveX("MoveX", InputAxis::Key);
    moveX.setPositiveKey(Keyboard::D);
    moveX.setNegativeKey(Keyboard::A);
    moveX.setAcceleration(4);
    moveX.setGravity(10);

    InputAxis moveY("MoveY", InputAxis::Key);
    moveY.setPositiveKey(Keyboard::W);
    moveY.setNegativeKey(Keyboard::S);
    moveY.setAcceleration(4);
    moveY.setGravity(10);

    InputAxis roll("Roll", InputAxis::Key);
    roll.setPositiveKey(Keyboard::E);
    roll.setNegativeKey(Keyboard::Q);
    roll.setAcceleration(4);
    roll.setGravity(10);

    InputAxis adjustSpeed("AdjustSpeed", InputAxis::MouseScroll);
    adjustSpeed.setAcceleration(4);
    adjustSpeed.setGravity(1000);

    InputAxis::Array axes;
    axes.push_back(viewX);
    axes.push_back(viewY);
    axes.push_back(moveX);
    axes.push_back(moveY);
    axes.push_back(roll);
    axes.push_back(adjustSpeed);

    engine.input().setAxes(axes);
}

void SolidBlackState::begin()
{
    Input& input = engine().input();
    input.keyboard().addListener(this);
    //input.mouse().setCursorLocked(true);
}

void SolidBlackState::end()
{
    Input& input = engine().input();
    input.keyboard().removeListener(this);
}

void SolidBlackState::notifyKeyboardEvent(const Keyboard::Event& event)
{
    if (event.type != Keyboard::Event::KeyDown)
    {
        return;
    }

    if (event.key == Keyboard::Esc)
    {
        setActive(false);
    }
    else if (event.key == Keyboard::Tab)
    {
        Mouse& mouse = engine().input().mouse();
        mouse.setCursorLocked(!mouse.isCursorLocked());
    }
    else if (event.key == Keyboard::F1)
    {
        if (_debugLevel == 1)
        {
            _debugLevel = 0;
        }
        else
        {
            _debugLevel = 1;
        }
    }
}

unsigned SolidBlackState::debugLevel() const
{
    return _debugLevel;
}