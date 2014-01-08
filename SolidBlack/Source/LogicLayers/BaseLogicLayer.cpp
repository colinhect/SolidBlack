#include "SolidBlack.h"

BaseLogicLayer::BaseLogicLayer(LogicFlow& logicFlow, InputSystem& inputSystem) :
    _logicFlow(&logicFlow),
    _inputSystem(&inputSystem)
{
    _inputSystem->keyboard().addListener(*this);
}

BaseLogicLayer::~BaseLogicLayer()
{
    _inputSystem->keyboard().removeListener(*this);
}

void BaseLogicLayer::receiveEvent(const KeyboardEvent& event)
{
    if (event.key == Key::Esc && event.type == KeyboardEventType::KeyDown)
    {
        _logicFlow->removeAllLayers();
    }
}