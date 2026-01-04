#include "ghedxpch.h"
#include "DxGraphicsFeature.h"

#include "engine/graphics/material/MaterialLoader.h"
#include "shader/DxShaderLoader.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxGraphicsFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphicsFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxGraphicsFeature::uninitGraphicsFeature() {
        resourceManager.Loaders.remove<Material>();
        resourceManager.Loaders.remove<DxShader>();
        shaderCompiler.set(nullptr);
        delete memoryManager;
        memoryManager = nullptr;
        graphics.uninit();
    }

    void DxGraphicsFeature::onInit() {
        graphics.init();
        shaderCompiler = makeShared<DxShaderCompiler>(graphics);
        auto shaderLoader = makeIntrusive<DxShaderLoader>(resourceManager, shaderCompiler.ref());
        shaderLoader->includeDirs.add(DirectoryPath(L"./resources/shaders/DirectX/"));
        resourceManager.Loaders.set<DxShader>(shaderLoader.ref());
        commandList = makeIntrusive<CommandList>();
        commandList->init(graphics, graphics.DirectQueue);
        textureFactory = makeShared<DxTextureFactory>(graphics, commandList.ref());
        memoryManager = ghnew DxGPUMemoryManager(graphics, commandList.ref());
        auto materialLoader = makeIntrusive<MaterialLoader>(resourceManager, textureFactory.ref(), *memoryManager);
        resourceManager.Loaders.set<Material>(materialLoader.ref());
    }

    void DxGraphicsFeature::onUninit() {
        uninitGraphicsFeature();
    }
}