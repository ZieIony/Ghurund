#include "utcpch.h"
#include "CppUnitTest.h"

#include <test/utils/MemoryGuard.h>
#include <DirectXMath.h>
#include <core/collection/Array.h>
#include <core/Buffer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace std;
    using namespace DirectX;
    using namespace Ghurund::Core;

    TEST_CLASS(BufferTest) {
public:

    TEST_METHOD(Buffer_copy) {
        MemoryGuard guard;
        {
            Array<XMFLOAT2> vertices = { {1,0}, {1,1}, {0,1} };
            Buffer buffer = Buffer(vertices.Data, vertices.Size);

            Buffer copy = buffer;

            Assert::IsTrue(buffer == copy);
            Assert::IsTrue(buffer.Data != copy.Data);
            Assert::IsTrue(buffer.Size == copy.Size);
        }
    }
    };
}
