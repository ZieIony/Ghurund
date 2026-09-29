#include "ghedxpch.h"
#include "DxGraphicsFeature.h"

#include "engine/graphics/material/MaterialLoader.h"
#include "engine/directx/rendering/DxGraphicsShaderLoader.h"
#include "engine/directx/cubemap/DxCubeMapLoader.h"
#include "texture/DxTextureLoader.h"
#include "compute/DxComputeShaderLoader.h"

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
        resourceManager.Loaders.remove<DxGraphicsShader>();
        shaderCompiler.set(nullptr);
        delete memoryManager;
        memoryManager = nullptr;
		graphics.uninit();
	}

	CoroutineTask<void> DxGraphicsFeature::onInit() {
		graphics.init();
		commandList = makeIntrusive<DxGraphicsCommandList>();
		commandList->init(graphics, graphics.DirectQueue);

		shaderCompiler = makeShared<DxShaderCompiler>(graphics);
		auto graphicsShaderLoader = makeIntrusive<DxGraphicsShaderLoader>(resourceManager, shaderCompiler.ref());
		graphicsShaderLoader->includeDirs.add(ResourceManager::ENGINE_LIB_PATH / DirectoryPath(L"/shaders/DirectX/include"));
		resourceManager.Loaders.set<DxGraphicsShader>(graphicsShaderLoader.ref());
		auto computeShaderLoader = makeIntrusive<DxComputeShaderLoader>(resourceManager, shaderCompiler.ref());
		computeShaderLoader->includeDirs.add(ResourceManager::ENGINE_LIB_PATH / DirectoryPath(L"/shaders/DirectX/include"));
		resourceManager.Loaders.set<DxComputeShader>(computeShaderLoader.ref());

		memoryManager = ghnew DxGPUMemoryManager(graphics, commandList.ref());
		auto materialLoader = makeIntrusive<MaterialLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<Material>(materialLoader.ref());

		auto textureLoader = makeIntrusive<DxTextureLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<DxTexture>(textureLoader.ref());
		auto cubeMapLoader = makeIntrusive<DxCubeMapLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<DxCubeMap>(cubeMapLoader.ref());

		meshLoader = makeIntrusive<DxMeshLoader>(*memoryManager);
		resourceManager.Loaders.set<DxMesh>(meshLoader.ref());

		resourceFactory = ghnew DxGraphicsResourceFactory(*memoryManager);

		co_return;
	}

	void DxGraphicsFeature::onUninit() {
		uninitGraphicsFeature();
	}
}
