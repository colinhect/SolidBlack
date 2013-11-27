#include "Hect.h"

using namespace hect;

InputAxis InputAxisDataFormat::load(const std::string& name, const DataValue& dataValue)
{
    InputAxisSource source = _parseSource(dataValue["source"]);
    InputAxis axis(name, source);

    if (!dataValue["positiveMouseButton"].isNull())
    {
        MouseButton button = _parseMouseButton(dataValue["positiveMouseButton"]);
        axis.setPositiveMouseButton(button);
    }

    if (!dataValue["negativeMouseButton"].isNull())
    {
        MouseButton button = _parseMouseButton(dataValue["negativeMouseButton"]);
        axis.setNegativeMouseButton(button);
    }

    if (!dataValue["positiveKey"].isNull())
    {
        Key key = _parseKey(dataValue["positiveKey"]);
        axis.setPositiveKey(key);
    }

    if (!dataValue["negativeKey"].isNull())
    {
        Key key = _parseKey(dataValue["negativeKey"]);
        axis.setNegativeKey(key);
    }

    if (dataValue["acceleration"].isNumber())
    {
        axis.setAcceleration(dataValue["acceleration"].asDouble());
    }
    
    if (dataValue["gravity"].isNumber())
    {
        axis.setGravity(dataValue["gravity"].asDouble());
    }

    return axis;
}

InputAxisSource InputAxisDataFormat::_parseSource(const DataValue& dataValue)
{
    static std::map<std::string, InputAxisSource> sources;

    if (sources.empty())
    {
        sources["MouseMoveX"] = InputAxisSource::MouseMoveX;
        sources["MouseMoveY"] = InputAxisSource::MouseMoveY;
        sources["MouseButton"] = InputAxisSource::MouseButton;
        sources["MouseScroll"] = InputAxisSource::MouseScroll;
        sources["Key"] = InputAxisSource::Key;
    }

    auto it = sources.find(dataValue.asString());
    if (it == sources.end())
    {
        throw Error(format("Invalid input axis source '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

Key InputAxisDataFormat::_parseKey(const DataValue& dataValue)
{
    static std::map<std::string, Key> keys;

    if (keys.empty())
    {
        keys["A"] = Key::A;
        keys["B"] = Key::B;
        keys["C"] = Key::C;
        keys["D"] = Key::D;
        keys["E"] = Key::E;
        keys["F"] = Key::F;
        keys["G"] = Key::G;
        keys["H"] = Key::H;
        keys["I"] = Key::I;
        keys["J"] = Key::J;
        keys["K"] = Key::K;
        keys["L"] = Key::L;
        keys["M"] = Key::M;
        keys["N"] = Key::N;
        keys["O"] = Key::O;
        keys["P"] = Key::P;
        keys["Q"] = Key::Q;
        keys["R"] = Key::R;
        keys["S"] = Key::S;
        keys["T"] = Key::T;
        keys["U"] = Key::U;
        keys["V"] = Key::V;
        keys["W"] = Key::W;
        keys["X"] = Key::X;
        keys["Y"] = Key::Y;
        keys["Z"] = Key::Z;
    }

    auto it = keys.find(dataValue.asString());
    if (it == keys.end())
    {
        throw Error(format("Invalid key '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}

MouseButton InputAxisDataFormat::_parseMouseButton(const DataValue& dataValue)
{
    static std::map<std::string, MouseButton> mouseButtons;

    if (mouseButtons.empty())
    {
        mouseButtons["Left"] = MouseButton::Left;
        mouseButtons["Right"] = MouseButton::Right;
        mouseButtons["Middle"] = MouseButton::Middle;
    }

    auto it = mouseButtons.find(dataValue.asString());
    if (it == mouseButtons.end())
    {
        throw Error(format("Invalid mouse button '%s'", dataValue.asString().c_str()));
    }

    return (*it).second;
}
