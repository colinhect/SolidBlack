#pragma once

class BaseLogicLayer :
    public LogicLayer,
    public KeyboardListener,
    public Uncopyable
{
public:
    BaseLogicLayer(LogicFlow& logicFlow, InputSystem& inputSystem);
    ~BaseLogicLayer();

    void receiveKeyboardEvent(const KeyboardEvent& event);

private:
    LogicFlow* _logicFlow;
    InputSystem* _inputSystem;
};