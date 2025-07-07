#include "utepch.h"
#include "CppUnitTest.h"

#include "graphics/mesh/Mesh.h"
#include <graphics/mesh/MeshLoader.h>
#include <test/MemoryGuard.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Engine;
    using namespace std;

    TEST_CLASS(MeshTest) {
public:

    TEST_METHOD(Mesh_position2d) {
        MemoryGuard guard;
        {
            List<XMFLOAT2> vertices = { {1,0}, {1,1}, {0,1} };
            List<uint32_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);

            auto mesh = makeIntrusive<Mesh>();
            mesh->init({ posStream }, vertices.Size, Buffer(indices.Data, sizeof(uint32_t) * indices.Size), indices.Size);

            Assert::AreEqual(3u, mesh->VertexCount);
            Assert::AreEqual(3u, mesh->IndexCount);
            Assert::AreEqual((uint32_t)sizeof(uint32_t), mesh->IndexSize);
            Assert::AreEqual(1ull, mesh->VertexStreams.Size);
        }
    }

    TEST_METHOD(Mesh_shortIndices) {
        MemoryGuard guard;
        {
            List<XMFLOAT3> vertices = { {1,0,0}, {1,1,0}, {0,1,0} };
            List<uint16_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);

            auto mesh = makeIntrusive<Mesh>();
            mesh->init({ posStream }, vertices.Size, indices);

            Assert::AreEqual(3u, mesh->VertexCount);
            Assert::AreEqual(3u, mesh->IndexCount);
            Assert::AreEqual((uint32_t)sizeof(uint16_t), mesh->IndexSize);
            Assert::AreEqual(1ull, mesh->VertexStreams.Size);
        }
    }
    };
}
