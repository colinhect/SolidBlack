#include "SolidBlack.h"

BaseLogicLayer::BaseLogicLayer(LogicFlow& logicFlow, InputSystem& inputSystem) :
    _logicFlow(&logicFlow),
    _inputSystem(&inputSystem)
{
    _inputSystem->keyboard().addObserver(*this);
}

BaseLogicLayer::~BaseLogicLayer()
{
    _inputSystem->keyboard().removeObserver(*this);
}

void BaseLogicLayer::receiveEvent(const KeyboardEvent& event)
{
    if (event.key == Key::Esc && event.type == KeyboardEventType::KeyDown)
    {
        _logicFlow->removeAllLayers();
    }
}