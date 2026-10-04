#include "ghedxpch.h"
#include "DxGraphicsFeature.h"

#include "engine/graphics/material/MaterialLoader.h"
#include "engine/directx/rendering/DxGraphicsShaderLoader.h"
#include "engine/directx/cubemap/DxCubeMapLoader.h"
#include "texture/DxTextureLoader.h"
#include "compute/DxComputeShaderLoader.h"
#include "mesh/DxMeshLoader.h"
#include "rendering/DxGraphicsCommandList.h"
#include "shader/compiler/DxShaderCompiler.h"
#include "engine/directx/rendering/DxRenderer.h"

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

		delete shaderCompiler;
        shaderCompiler = nullptr;

        delete memoryManager;
		memoryManager = nullptr;

		delete renderer;
		renderer = nullptr;

		commandList->release();
		commandList = nullptr;

		delete graphics;
		graphics = nullptr;
	}

	CoroutineTask<void> DxGraphicsFeature::onInit() {
		co_await __super::onInit();

		graphics = ghnew DxGraphics();
		graphics->init();

		commandList = ghnew DxGraphicsCommandList();
		commandList->init(*graphics, graphics->DirectQueue);

		renderer = ghnew DxRenderer(*graphics);
		renderer->init();

		shaderCompiler = ghnew DxShaderCompiler(*graphics);
		auto graphicsShaderLoader = makeIntrusive<DxGraphicsShaderLoader>(resourceManager, *shaderCompiler);
		graphicsShaderLoader->includeDirs.add(ResourceManager::ENGINE_LIB_PATH / DirectoryPath(L"/shaders/DirectX/include"));
		resourceManager.Loaders.set<DxGraphicsShader>(graphicsShaderLoader.ref());
		auto computeShaderLoader = makeIntrusive<DxComputeShaderLoader>(resourceManager, *shaderCompiler);
		computeShaderLoader->includeDirs.add(ResourceManager::ENGINE_LIB_PATH / DirectoryPath(L"/shaders/DirectX/include"));
		resourceManager.Loaders.set<DxComputeShader>(computeShaderLoader.ref());

		memoryManager = ghnew DxGPUMemoryManager(*graphics, *commandList);
		auto materialLoader = makeIntrusive<MaterialLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<Material>(materialLoader.ref());

		auto textureLoader = makeIntrusive<DxTextureLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<DxTexture>(textureLoader.ref());
		auto cubeMapLoader = makeIntrusive<DxCubeMapLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<DxCubeMap>(cubeMapLoader.ref());

		auto meshLoader = makeIntrusive<DxMeshLoader>(*memoryManager);
		resourceManager.Loaders.set<DxMesh>(meshLoader.ref());

		resourceFactory = ghnew DxGraphicsResourceFactory(*memoryManager);

		co_return;
	}

	void DxGraphicsFeature::onUninit() {
		uninitGraphicsFeature();
		__super::onUninit();
	}
}
