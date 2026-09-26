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
		delete resourceFactory;
		resourceFactory = nullptr;
		resourceManager.Loaders.remove<DxTexture>();
		resourceManager.Loaders.remove<Material>();
        resourceManager.Loaders.remove<DxShader>();
        shaderCompiler.set(nullptr);
        delete memoryManager;
        memoryManager = nullptr;
		graphics.uninit();
	}

	CoroutineTask<void> DxGraphicsFeature::onInit() {
		graphics.init();
		commandList = makeIntrusive<CommandList>();
		commandList->init(graphics, graphics.DirectQueue);

		shaderCompiler = makeShared<DxShaderCompiler>(graphics);
		auto shaderLoader = makeIntrusive<DxShaderLoader>(resourceManager, shaderCompiler.ref());
		shaderLoader->includeDirs.add(ResourceManager::ENGINE_LIB_PATH / DirectoryPath(L"/shaders/DirectX/include"));
		resourceManager.Loaders.set<DxShader>(shaderLoader.ref());

		auto textureLoader = makeIntrusive<DxTextureLoader>(resourceManager, graphics, commandList.ref());
		resourceManager.Loaders.set<DxTexture>(textureLoader.ref());

		memoryManager = ghnew DxGPUMemoryManager(graphics, commandList.ref());
		auto materialLoader = makeIntrusive<MaterialLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<Material>(materialLoader.ref());

		meshLoader = makeIntrusive<DxMeshLoader>(*memoryManager);
		resourceManager.Loaders.set<DxMesh>(meshLoader.ref());

		resourceFactory = ghnew DxGraphicsResourceFactory(*memoryManager, graphics, commandList.ref());

		co_return;
	}

	void DxGraphicsFeature::onUninit() {
		uninitGraphicsFeature();
	}
}
