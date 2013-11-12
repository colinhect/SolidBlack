#include "Hect.h"

using namespace hect;

void Window::bind(Gpu* gpu)
{
    gpu->bindWindow(*this);
}