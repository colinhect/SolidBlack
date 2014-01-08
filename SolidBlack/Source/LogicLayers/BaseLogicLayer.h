#pragma once

class BaseLogicLayer :
    public LogicLayer,
    public Observer<KeyboardEvent>,
    public Uncopyable
{
public:
    BaseLogicLayer(LogicFlow& logicFlow, InputSystem& inputSystem);
    ~BaseLogicLayer();

    void receiveEvent(const KeyboardEvent& event);

private:
    LogicFlow* _logicFlow;
    InputSystem* _inputSystem;
};