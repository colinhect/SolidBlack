#include <UnitTest++.h>

#include <Hect.h>

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

using namespace hect;

Engine* engine;
const double epsilon = 0.0001;

#include "AssetCacheTests.h"
#include "ClientServerTests.h"
#include "MaterialLoadingTests.h"
#include "MeshLoadingTests.h"
#include "TaskPoolTests.h"

int main()
{
    Engine engine("HectSystemTests", "HectSystemTestsSettings.json");
    ::engine = &engine;

    int failed = UnitTest::RunAllTests();
    if (failed)
    {
        Engine::fatalError(format("%d failures.", failed));
    }

    return failed;
}