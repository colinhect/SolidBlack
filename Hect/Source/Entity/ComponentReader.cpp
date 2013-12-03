#include "Hect.h"

using namespace hect;

ComponentDataValueReader::ComponentDataValueReader(const DataValue& dataValue) :
    _dataValue(&dataValue)
{
}

double ComponentDataValueReader::readNumber(const char* name)
{
    return (*_dataValue)[name].asDouble();
}

std::string ComponentDataValueReader::readString(const char* name)
{
    return (*_dataValue)[name].asString();
}

Vector2<> ComponentDataValueReader::readVector2(const char* name)
{
    return (*_dataValue)[name].asVector2();
}

Vector3<> ComponentDataValueReader::readVector3(const char* name)
{
    return (*_dataValue)[name].asVector3();
}

Vector4<> ComponentDataValueReader::readVector4(const char* name)
{
    return (*_dataValue)[name].asVector4();
}

Quaternion<> ComponentDataValueReader::readQuaternion(const char* name)
{
    return (*_dataValue)[name].asQuaternion();
}