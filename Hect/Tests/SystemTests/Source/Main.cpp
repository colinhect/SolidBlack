#include <UnitTest++.h>

#include <Hect.h>

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

using namespace hect;

const double epsilon = 0.0001;

#include "AssetCacheTests.h"
#include "EntityTests.h"
#include "MaterialLoadingTests.h"
#include "MeshLoadingTests.h"
#include "NetworkTests.h"
#include "TaskPoolTests.h"
#include "FileSystemTests.h"

int main()
{
    int failed = UnitTest::RunAllTests();
    if (failed)
    {
        Window::showFatalError(format("%d failures.", failed));
    }

    return failed;
}