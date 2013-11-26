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
#include "DataValueTests.h"
#include "FormatTests.h"
#include "FrustumTests.h"
#include "JsonParserTests.h"
#include "Matrix4Tests.h"
#include "MemoryStreamTests.h"
#include "MeshBuilderTests.h"
#include "MeshTests.h"
#include "PathTests.h"
#include "PlaneTests.h"
#include "QuaternionTests.h"
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