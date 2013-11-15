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
#include "MaterialLoadingTests.h"
#include "MeshLoadingTests.h"
#include "NetworkTests.h"
#include "TaskPoolTests.h"
#include "StorageTests.h"

int main()
{
    Engine engine("HectSystemTests", "HectSystemTestsSettings.json");
    ::engine = &engine;

    Storage& storage = engine.storage();
    Path workingDirectory = storage.workingDirectory();
    storage.addDataSource(workingDirectory);
    storage.setWriteDirectory(workingDirectory);

    int failed = UnitTest::RunAllTests();
    if (failed)
    {
        Engine::fatalError(format("%d failures.", failed));
    }

    return failed;
}