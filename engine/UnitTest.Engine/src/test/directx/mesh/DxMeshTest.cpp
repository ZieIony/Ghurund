#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/graphics/mesh/Mesh.h"
#include <engine/directx/mesh/DxMesh.h>
#include <engine/graphics/mesh/MeshLoader.h>
#include <test/MemoryGuard.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace ::DirectX;
    using namespace std;

    TEST_CLASS(DxMeshTest) {
public:

    TEST_METHOD(DxMesh_init) {
        MemoryGuard guard;
        {
            List<XMFLOAT3> vertices = { {1,0,0}, {1,1,0}, {0,1,0} };
            List<uint32_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);

            auto mesh = makeIntrusive<Mesh>();
            mesh->init({ posStream }, vertices.Size, indices);
            auto dxMesh = makeIntrusive<DxMesh>();
            auto graphics = makeIntrusive<Graphics>();
            graphics->init();
            auto commandList = makeIntrusive<CommandList>();
            commandList->init(*graphics.get(), graphics->CopyQueue);
            dxMesh->init(*mesh.get(), *graphics.get(), *commandList.get());

            Assert::IsTrue(mesh->Valid);
        }
    }
    };
}
