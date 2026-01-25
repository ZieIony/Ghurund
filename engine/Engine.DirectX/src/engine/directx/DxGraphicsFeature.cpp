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
		resourceManager.Loaders.remove<DxTexture>();
		resourceManager.Loaders.remove<Material>();
        resourceManager.Loaders.remove<DxShader>();
		imageLoader.set(nullptr);
        shaderCompiler.set(nullptr);
        delete memoryManager;
        memoryManager = nullptr;
		graphics.uninit();
	}

	void DxGraphicsFeature::onInit() {
		graphics.init();
		commandList = makeIntrusive<CommandList>();
		commandList->init(graphics, graphics.DirectQueue);

		shaderCompiler = makeShared<DxShaderCompiler>(graphics);
		auto shaderLoader = makeIntrusive<DxShaderLoader>(resourceManager, shaderCompiler.ref());
		shaderLoader->includeDirs.add(DirectoryPath(L"./resources/shaders/DirectX/include"));
		resourceManager.Loaders.set<DxShader>(shaderLoader.ref());

		imageLoader = makeIntrusive<ImageLoader>();
		auto textureLoader = makeIntrusive<DxTextureLoader>(imageLoader.ref(), graphics, commandList.ref());
		resourceManager.Loaders.set<DxTexture>(textureLoader.ref());

		memoryManager = ghnew DxGPUMemoryManager(graphics, commandList.ref());
		auto materialLoader = makeIntrusive<MaterialLoader>(resourceManager, *memoryManager);
		resourceManager.Loaders.set<Material>(materialLoader.ref());
	}

	void DxGraphicsFeature::onUninit() {
		uninitGraphicsFeature();
	}
}