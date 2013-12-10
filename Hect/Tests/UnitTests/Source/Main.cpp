#include <UnitTest++.h>

#include <Hect.h>

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

using namespace hect;

const double epsilon = 0.0001;

#include "AngleTests.h"
#include "AnyTests.h"
#include "AssetCacheTests.h"
#include "DataValueJsonFormatTests.h"
#include "DataReaderWriterTests.h"
#include "DataValueTests.h"
#include "EntityTests.h"
#include "FileSystemTests.h"
#include "FormatTests.h"
#include "FrustumTests.h"
#include "MaterialDataFormatTests.h"
#include "Matrix4Tests.h"
#include "MemoryStreamTests.h"
#include "MeshDataFormatTests.h"
#include "MeshTests.h"
#include "MeshWriterTests.h"
#include "MeshReaderTests.h"
#include "NetworkTests.h"
#include "PathTests.h"
#include "PlaneTests.h"
#include "QuaternionTests.h"
#include "SceneTests.h"
#include "StateFlowTests.h"
#include "TaskPoolTests.h"
#include "TimeSpanTests.h"
#include "Vector2Tests.h"
#include "Vector3Tests.h"
#include "Vector4Tests.h"
#include "VertexAttributeTests.h"
#include "VertexLayoutTests.h"

int main()
{
    int failed = UnitTest::RunAllTests();
    if (failed)
    {
        Window::showFatalError(format("%d failures.", failed));
    }

    return failed;
}