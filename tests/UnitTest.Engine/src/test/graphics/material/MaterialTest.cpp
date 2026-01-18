#include "utepch.h"
#include "CppUnitTest.h"

#include "core/io/File.h"
#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/directx/DxGraphics.h"
#include "engine/directx/shader/DxShaderLoader.h"
#include "engine/parameter/ValueParameter.h"
#include "test/utils/MemoryGuard.h"
#include "engine/graphics/material/Material.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace std;

    TEST_CLASS(MaterialTest) {
private:
    WString resDir = RES_DIR;

    ResourceManager resourceManager;
    DxGraphics graphics;
    IntrusivePointer<CommandList> commandList;
    SharedPointer<DxGPUMemoryManager> memoryManager;
    SharedPointer<DxShaderCompiler> shaderCompiler;
    IntrusivePointer<DxShaderLoader> shaderLoader;

    AString loadShaderSource(const WString& path) {
        File file = FilePath(resDir + path);
        Buffer buffer;
        file.read(buffer);
        return AString((const char*)buffer.Data, buffer.Size);
    }

public:
    MaterialTest() {
        graphics.init();
        commandList = makeIntrusive<CommandList>();
        commandList->init(graphics, graphics.CopyQueue);
        memoryManager = makeShared<DxGPUMemoryManager>(graphics, commandList.ref());
        shaderCompiler = makeShared<DxShaderCompiler>(graphics);
        shaderLoader = makeIntrusive<DxShaderLoader>(resourceManager, shaderCompiler.ref());
    }

    TEST_METHOD(Material_constructor) {
        MemoryGuard guard;
        {
            AString testShaderSource = loadShaderSource(L"/shaders/DirectX/ui.hlsl");
            MemoryInputStream stream(testShaderSource.Data, testShaderSource.Size);
            IntrusivePointer<DxShader> shader((DxShader*)shaderLoader->load(stream, DirectoryPath()));
            auto material = makeIntrusive<Material>(memoryManager.ref());
            material->Shader = shader.get();
        }
    }

    TEST_METHOD(Material_clone) {
        MemoryGuard guard;
        {
            AString testShaderSource = loadShaderSource(L"/shaders/DirectX/ui.hlsl");
            MemoryInputStream stream(testShaderSource.Data, testShaderSource.Size);
            IntrusivePointer<DxShader> shader((DxShader*)shaderLoader->load(stream, DirectoryPath()));
            auto material = makeIntrusive<Material>(memoryManager.ref());
            material->Shader = shader.get();
            auto material2 = IntrusivePointer<Material>((Material*)material->clone());
            material.set(nullptr);
        }
    }
    };
}
