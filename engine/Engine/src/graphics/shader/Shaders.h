#pragma once

#include "graphics/shader/Shader.h"
#include "core/string/TextUtils.h"

#include <format>

namespace Ghurund {
    class Shaders {
    private:
        Shaders() = delete;

        static Shader* load(ResourceManager& manager, const wchar_t* fileName) {
            auto path = std::format(L"{}{}{}", ResourceManager::LIB_PROTOCOL, ResourceManager::ENGINE_LIB_NAME, fileName);
            return manager.load<Shader>(FilePath(path.c_str()));
        }

    public:
        static Shader* loadBasic(ResourceManager& manager) {
            return load(manager, L"/shaders/basic.hlsl");
        }

        static Shader* loadBasicLight(ResourceManager& manager) {
            return load(manager, L"/shaders/basicLight.hlsl");
        }

        static Shader* loadToon(ResourceManager& manager) {
            return load(manager, L"/shaders/toon.hlsl");
        }

        static Shader* loadWireframe(ResourceManager& manager) {
            return load(manager, L"/shaders/wireframe.hlsl");
        }

        static Shader* loadOutline(ResourceManager& manager) {
            return load(manager, L"/shaders/outline.hlsl");
        }

        static Shader* loadNormals(ResourceManager& manager) {
            return load(manager, L"/shaders/normals.hlsl");
        }

        static Shader* loadInvalid(ResourceManager& manager) {
            return load(manager, L"/shaders/invalid.hlsl");
        }

        static Shader* loadLightPass(ResourceManager& manager) {
            return load(manager, L"/shaders/lightPass.hlsl");
        }

        static Shader* loadUi(ResourceManager& manager) {
            return load(manager, L"/shaders/ui.hlsl");
        }

        static Shader* loadBasicSky(ResourceManager& manager) {
            return load(manager, L"/shaders/basicSky.hlsl");
        }

        static Shader* loadAdvancedSky(ResourceManager& manager) {
            return load(manager, L"/shaders/advancedSky.hlsl");
        }
    };
}