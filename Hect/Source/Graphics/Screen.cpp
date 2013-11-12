#include "Hect.h"

using namespace hect;

void Screen::bind(Gpu* gpu)
{
    gpu->bindScreen(*this);
}