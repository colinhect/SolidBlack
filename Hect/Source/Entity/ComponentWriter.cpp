#include "Hect.h"

using namespace hect;

void ComponentDataValueWriter::writeNumber(const char* name, double value)
{
    _members[name] = value;
}

void ComponentDataValueWriter::writeString(const char* name, const std::string& value)
{
    _members[name] = value;
}

void ComponentDataValueWriter::writeVector2(const char* name, const Vector2<>& value)
{
    _members[name] = value;
}

void ComponentDataValueWriter::writeVector3(const char* name, const Vector3<>& value)
{
    _members[name] = value;
}

void ComponentDataValueWriter::writeVector4(const char* name, const Vector4<>& value)
{
    _members[name] = value;
}

void ComponentDataValueWriter::writeQuaternion(const char* name, const Quaternion<>& value)
{
    _members[name] = value;
}

DataValue ComponentDataValueWriter::dataValue() const
{
    return DataValue(_members);
}