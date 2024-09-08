#pragma once

#include "engine/directx/shader/Shader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Engine::DirectX;

    class ShaderProvider {
    private:
        ResourceManager& manager;

        inline Shader* load(const WString& fileName) {
            return manager.load<Shader>(ResourcePath(ResourceManager::ENGINE_LIB_NAME, fileName), DirectoryPath());
        }

    public:
        ShaderProvider(ResourceManager& manager):manager(manager) {}

        Shader* loadBasic() {
            return load(L"/shaders/basic.hlsl");
        }

        Shader* loadBasicLight() {
            return load(L"/shaders/basicLight.hlsl");
        }

        Shader* loadToon() {
            return load(L"/shaders/toon.hlsl");
        }

        Shader* loadWireframe() {
            return load(L"/shaders/wireframe.hlsl");
        }

        Shader* loadOutline() {
            return load(L"/shaders/outline.hlsl");
        }

        Shader* loadNormals() {
            return load(L"/shaders/normals.hlsl");
        }

        Shader* loadInvalid() {
            return load(L"/shaders/invalid.hlsl");
        }

        Shader* loadLightPass() {
            return load(L"/shaders/lightPass.hlsl");
        }

        Shader* loadUi() {
            return load(L"/shaders/ui.hlsl");
        }

        Shader* loadBasicSky() {
            return load(L"/shaders/basicSky.hlsl");
        }

        Shader* loadAdvancedSky() {
            return load(L"/shaders/advancedSky.hlsl");
        }
    };
}