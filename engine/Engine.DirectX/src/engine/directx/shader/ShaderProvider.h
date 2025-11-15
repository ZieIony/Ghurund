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

        ShaderProvider& operator=(const ShaderProvider& other) = delete;

    public:
        ShaderProvider(ResourceManager& manager):manager(manager) {}

        DxShader* loadBasic() {
            return load(L"/shaders/DirectX/basic.hlsl");
        }

        DxShader* loadBasicLight() {
            return load(L"/shaders/DirectX/basicLight.hlsl");
        }

        DxShader* loadToon() {
            return load(L"/shaders/DirectX/toon.hlsl");
        }

        DxShader* loadWireframe() {
            return load(L"/shaders/DirectX/wireframe.hlsl");
        }

        DxShader* loadOutline() {
            return load(L"/shaders/DirectX/outline.hlsl");
        }

        DxShader* loadNormals() {
            return load(L"/shaders/DirectX/normals.hlsl");
        }

        DxShader* loadInvalid() {
            return load(L"/shaders/DirectX/invalid.hlsl");
        }

        DxShader* loadLightPass() {
            return load(L"/shaders/DirectX/lightPass.hlsl");
        }

        DxShader* loadUi() {
            return load(L"/shaders/DirectX/ui.hlsl");
        }

        DxShader* loadText() {
            return load(L"/shaders/DirectX/text.hlsl");
        }

        DxShader* loadBasicSky() {
            return load(L"/shaders/DirectX/basicSky.hlsl");
        }

        DxShader* loadAdvancedSky() {
            return load(L"/shaders/DirectX/advancedSky.hlsl");
        }
    };
}