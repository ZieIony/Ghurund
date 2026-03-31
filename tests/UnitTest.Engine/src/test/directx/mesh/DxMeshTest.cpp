#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/directx/DxGraphics.h"
#include "engine/directx/mesh/DxMesh.h"
#include "engine/graphics/mesh/MeshData.h"
#include "test/utils/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace ::DirectX;
    using namespace std;

    TEST_CLASS(DxMeshTest) {
private:
            Timer timer;
            CoroutineThreadPool threadPool = CoroutineThreadPool(4);
            CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
            ResourceManager resourceManager = coroutineScheduler;
            DxGraphics graphics;

public:

    TEST_METHOD(DxMesh_init) {
        MemoryGuard guard;
        {
            Array<XMFLOAT3> vertices = { {1,0,0}, {1,1,0}, {0,1,0} };
            Array<uint32_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);

            auto mesh = makeIntrusive<MeshData>();
            mesh->init({ posStream }, (uint32_t)vertices.Size, indices);
            auto dxMesh = makeIntrusive<DxMesh>();
            graphics.init();
            auto commandList = makeIntrusive<CommandList>();
            commandList->init(graphics, graphics.CopyQueue);
            DxGPUMemoryManager memoryManager(graphics, commandList.ref());
            dxMesh->init(*mesh.get(), memoryManager);

            Assert::IsTrue(mesh->IsValid);
        }
    }
    };
}
