#include "utepch.h"
#include "CppUnitTest.h"

#include "core/math/Vector.h"
#include "engine/graphics/mesh/MeshData.h"
#include "test/utils/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Engine;
    using namespace std;

    TEST_CLASS(MeshDataTest) {
public:

    TEST_METHOD(MeshData_position2d) {
        MemoryGuard guard;
        {
            Array<XMFLOAT2> vertices = { {1,0}, {1,1}, {0,1} };
            Array<uint32_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);
            BoundingBox boundingBox;

            auto mesh = makeIntrusive<MeshData>();
            mesh->init({ posStream }, vertices.Size, Buffer(indices.Data, sizeof(uint32_t) * indices.Size), (uint32_t)indices.Size, boundingBox);

            Assert::AreEqual(3u, mesh->VertexCount);
            Assert::AreEqual(3u, mesh->IndexCount);
            Assert::AreEqual((uint32_t)sizeof(uint32_t), mesh->IndexSize);
            Assert::AreEqual(1ull, mesh->VertexStreams.Size);
            Assert::IsTrue(XMFLOAT3(0, 0, 0) == mesh->BoundingBox.Center);
            Assert::IsTrue(XMFLOAT3(1, 1, 1) == mesh->BoundingBox.Extents);
        }
    }

    TEST_METHOD(MeshData_shortIndices) {
        MemoryGuard guard;
        {
            Array<XMFLOAT3> vertices = { {1,0,0}, {1,1,0}, {0,1,0} };
            Array<uint16_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);
            BoundingBox boundingBox;

            auto mesh = makeIntrusive<MeshData>();
            mesh->init({ posStream }, vertices.Size, indices, boundingBox);

            Assert::AreEqual(3u, mesh->VertexCount);
            Assert::AreEqual(3u, mesh->IndexCount);
            Assert::AreEqual((uint32_t)sizeof(uint16_t), mesh->IndexSize);
            Assert::AreEqual(1ull, mesh->VertexStreams.Size);
            Assert::IsTrue(XMFLOAT3(0, 0, 0) == mesh->BoundingBox.Center);
            Assert::IsTrue(XMFLOAT3(1, 1, 1) == mesh->BoundingBox.Extents);
        }
    }
    };
}
