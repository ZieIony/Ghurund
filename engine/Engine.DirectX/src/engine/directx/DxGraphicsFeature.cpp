#include "ghedxpch.h"
#include "DxGraphicsFeature.h"

#include "shader/DxShaderLoader.h"
#include "material/DxMaterialLoader.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxGraphicsFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphicsFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxGraphicsFeature::uninitGraphicsFeature() {
        resourceManager.Loaders.remove<IMaterial>();
        resourceManager.Loaders.remove<DxShader>();
        materialFactory.set(nullptr);
        shaderCompiler.set(nullptr);
        graphics.uninit();
    }

    void DxGraphicsFeature::onInit() {
        graphics.init();
        shaderCompiler = makeShared<DxShaderCompiler>(graphics);
        auto shaderLoader = makeIntrusive<DxShaderLoader>(shaderCompiler.ref());
        shaderLoader->includeDirs.add(DirectoryPath(L"./resources/shaders/DirectX/"));
        resourceManager.Loaders.set<DxShader>(shaderLoader.ref());
        materialFactory = makeShared<DxMaterialFactory>();
        commandList = makeIntrusive<CommandList>();
        commandList->init(graphics, graphics.DirectQueue);
        textureFactory = makeShared<DxTextureFactory>(graphics, commandList.ref());
        auto materialLoader = makeIntrusive<DxMaterialLoader>(resourceManager, materialFactory.ref(), textureFactory.ref());
        resourceManager.Loaders.set<IMaterial>(materialLoader.ref());
    }

    void DxGraphicsFeature::onUninit() {
        uninitGraphicsFeature();
    }
}