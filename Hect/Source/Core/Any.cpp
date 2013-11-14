#include "Any.h"

using namespace hect;

Any::Any() :
    _container(nullptr)
{
}

Any::Any(Any&& any) :
    _container(any._container)
{
    any._container = nullptr;
}

Any::Any(const Any& any) :
    _container(any._container ? any._container->clone() : nullptr)
{
}

Any::~Any()
{
    if (_container)
    {
        delete _container;
    }
}

Any& Any::operator=(const Any& any)
{
    if (_container)
    {
        delete _container;
    }

    _container = any._container ? any._container->clone() : nullptr;

    return *this;
}

bool Any::hasValue() const
{
    return _container != nullptr;
}