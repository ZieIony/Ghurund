#pragma once

#include "engine/directx/shader/DxShader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Engine::DirectX;

    class ShaderProvider {
    private:
        ResourceManager& manager;

        inline DxShader* load(const WString& fileName) {
            return manager.load<DxShader>(ResourcePath(ResourceManager::ENGINE_LIB_NAME, fileName), DirectoryPath());
        }

    public:
        ShaderProvider(ResourceManager& manager):manager(manager) {}

        DxShader* loadBasic() {
            return load(L"/shaders/basic.hlsl");
        }

        DxShader* loadBasicLight() {
            return load(L"/shaders/basicLight.hlsl");
        }

        DxShader* loadToon() {
            return load(L"/shaders/toon.hlsl");
        }

        DxShader* loadWireframe() {
            return load(L"/shaders/wireframe.hlsl");
        }

        DxShader* loadOutline() {
            return load(L"/shaders/outline.hlsl");
        }

        DxShader* loadNormals() {
            return load(L"/shaders/normals.hlsl");
        }

        DxShader* loadInvalid() {
            return load(L"/shaders/invalid.hlsl");
        }

        DxShader* loadLightPass() {
            return load(L"/shaders/lightPass.hlsl");
        }

        DxShader* loadUi() {
            return load(L"/shaders/ui.hlsl");
        }

        DxShader* loadBasicSky() {
            return load(L"/shaders/basicSky.hlsl");
        }

        DxShader* loadAdvancedSky() {
            return load(L"/shaders/advancedSky.hlsl");
        }
    };
}