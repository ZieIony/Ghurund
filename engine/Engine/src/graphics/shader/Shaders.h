#pragma once

#include "graphics/shader/Shader.h"
#include "core/string/TextUtils.h"

#include <fmt/format.h>

namespace Ghurund {
    class Shaders {
    private:
        Shaders() = delete;

        static Shader* load(ResourceContext& context, const wchar_t* fileName) {
            auto path = fmt::format(L"{}{}{}", ResourceManager::LIB_PROTOCOL_PREFIX, ResourceManager::ENGINE_LIB_NAME, fileName).c_str();
            return context.ResourceManager.load<Shader>(context, FilePath(path));
        }

    public:
        static Shader* loadBasic(ResourceContext& context) {
            return load(context, L"/shaders/basic.hlsl");
        }

        static Shader* loadBasicLight(ResourceContext& context) {
            return load(context, L"/shaders/basicLight.hlsl");
        }

        static Shader* loadToon(ResourceContext& context) {
            return load(context, L"/shaders/toon.hlsl");
        }

        static Shader* loadWireframe(ResourceContext& context) {
            return load(context, L"/shaders/wireframe.hlsl");
        }

        static Shader* loadOutline(ResourceContext& context) {
            return load(context, L"/shaders/outline.hlsl");
        }

        static Shader* loadNormals(ResourceContext& context) {
            return load(context, L"/shaders/normals.hlsl");
        }

        static Shader* loadInvalid(ResourceContext& context) {
            return load(context, L"/shaders/invalid.hlsl");
        }

        static Shader* loadLightPass(ResourceContext& context) {
            return load(context, L"/shaders/lightPass.hlsl");
        }

        static Shader* loadUi(ResourceContext& context) {
            return load(context, L"/shaders/ui.hlsl");
        }

        static Shader* loadBasicSky(ResourceContext& context) {
            return load(context, L"/shaders/basicSky.hlsl");
        }

        static Shader* loadAdvancedSky(ResourceContext& context) {
            return load(context, L"/shaders/advancedSky.hlsl");
        }
    };
}