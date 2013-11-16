#pragma once

namespace
{

///
/// An object that cannot be copied.
class Uncopyable
{
protected:
    Uncopyable() { }
    ~Uncopyable() { }
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

}