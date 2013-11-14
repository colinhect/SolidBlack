#include "Hect.h"

using namespace hect;

Vector2<> JsonFormat::parseVector2(const DataValue& dataValue) const
{
    Vector2<> result;

    size_t i = 0;
    for (const DataValue& component : dataValue)
    {
        if (i < 2)
        {
            result[i++] = (double)component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

Vector3<> JsonFormat::parseVector3(const DataValue& dataValue) const
{
    Vector3<> result;

    size_t i = 0;
    for (const DataValue& component : dataValue)
    {
        if (i < 3)
        {
            result[i++] = (double)component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

Vector4<> JsonFormat::parseVector4(const DataValue& dataValue) const
{
    Vector4<> result;

    size_t i = 0;
    for (const DataValue& component : dataValue)
    {
        if (i < 4)
        {
            result[i++] = (double)component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}

Matrix4<> JsonFormat::parseMatrix4(const DataValue& dataValue) const
{
    Matrix4<> result;

    size_t i = 0;
    for (const DataValue& component : dataValue)
    {
        if (i < 16)
        {
            result[i++] = (double)component.asDouble();
        }
        else
        {
            break;
        }
    }

    return result;
}
