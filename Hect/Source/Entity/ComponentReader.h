#pragma once

namespace hect
{

class ComponentReader :
    public Uncopyable
{
public:
    virtual double readNumber(const char* name) = 0;
    virtual std::string readString(const char* name) = 0;
    virtual Vector2<> readVector2(const char* name) = 0;
    virtual Vector3<> readVector3(const char* name) = 0;
    virtual Vector4<> readVector4(const char* name) = 0;
    virtual Quaternion<> readQuaternion(const char* name) = 0;
};

class ComponentDataValueReader :
    public ComponentReader
{
public:
    ComponentDataValueReader(const DataValue& dataValue);
    
    double readNumber(const char* name);
    std::string readString(const char* name);
    Vector2<> readVector2(const char* name);
    Vector3<> readVector3(const char* name);
    Vector4<> readVector4(const char* name);
    Quaternion<> readQuaternion(const char* name);

private:
    const DataValue* _dataValue;
};

}