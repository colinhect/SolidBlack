#include "SolidBlackState.h"

SolidBlackState::SolidBlackState(Engine& engine, double timeStep) :
    State(engine, timeStep),
    _debugLevel(0)
{
    // Create the input axes
    InputAxis viewX("ViewX", InputAxisSource::MouseMoveX);
    viewX.setAcceleration(0.0025);
    viewX.setGravity(10);

    InputAxis viewY("ViewY", InputAxisSource::MouseMoveY);
    viewY.setAcceleration(0.0025);
    viewY.setGravity(10);

    InputAxis moveX("MoveX", InputAxisSource::Key);
    moveX.setPositiveKey(Key::D);
    moveX.setNegativeKey(Key::A);
    moveX.setAcceleration(4);
    moveX.setGravity(10);

    InputAxis moveY("MoveY", InputAxisSource::Key);
    moveY.setPositiveKey(Key::W);
    moveY.setNegativeKey(Key::S);
    moveY.setAcceleration(4);
    moveY.setGravity(10);

    InputAxis roll("Roll", InputAxisSource::Key);
    roll.setPositiveKey(Key::E);
    roll.setNegativeKey(Key::Q);
    roll.setAcceleration(4);
    roll.setGravity(10);

    InputAxis adjustSpeed("AdjustSpeed", InputAxisSource::MouseScroll);
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
    input.keyboard().addListener(*this);
    input.mouse().setCursorLocked(true);
}

void SolidBlackState::end()
{
    Input& input = engine().input();
    input.keyboard().removeListener(*this);
}

void SolidBlackState::receiveKeyboardEvent(const KeyboardEvent& event)
{
    if (event.type != KeyboardEventType::KeyDown)
    {
        return;
    }

    if (event.key == Key::Esc)
    {
        setActive(false);
    }
    else if (event.key == Key::Tab)
    {
        Mouse& mouse = engine().input().mouse();
        mouse.setCursorLocked(!mouse.isCursorLocked());
    }
    else if (event.key == Key::F1)
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