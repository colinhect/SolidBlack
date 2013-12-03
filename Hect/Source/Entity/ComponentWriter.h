#pragma once

namespace hect
{

class ComponentWriter :
    public Uncopyable
{
public:
    virtual void writeNumber(const char* name, double value) = 0;
    virtual void writeString(const char* name, const std::string& value) = 0;
    virtual void writeVector2(const char* name, const Vector2<>& value) = 0;
    virtual void writeVector3(const char* name, const Vector3<>& value) = 0;
    virtual void writeVector4(const char* name, const Vector4<>& value) = 0;
    virtual void writeQuaternion(const char* name, const Quaternion<>& value) = 0;
};

class ComponentDataValueWriter :
    public ComponentWriter
{
public:
    void writeNumber(const char* name, double value);
    void writeString(const char* name, const std::string& value);
    void writeVector2(const char* name, const Vector2<>& value);
    void writeVector3(const char* name, const Vector3<>& value);
    void writeVector4(const char* name, const Vector4<>& value);
    void writeQuaternion(const char* name, const Quaternion<>& value);

    DataValue dataValue() const; 

private:
    DataValue::Object _members;
};

}