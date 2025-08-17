#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/graphics/mesh/VertexStream.h"
#include <test/MemoryGuard.h>
#include <DirectXMath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Engine;
    using namespace std;
    using namespace DirectX;

    TEST_CLASS(VertexStreamTest) {
public:

    TEST_METHOD(VertexStream_copy) {
        MemoryGuard guard;
        {
            Array<XMFLOAT2> vertices = { {1,0}, {1,1}, {0,1} };
            Array<uint32_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);

            VertexStream copy = posStream;

            Assert::IsTrue(posStream.data == copy.data);
            Assert::IsTrue(posStream.vertexSize == copy.vertexSize);
            Assert::IsTrue(posStream.role == copy.role);
        }
    }
    };
}
