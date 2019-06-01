#pragma once

#include "graphics/shader/Shader.h"

namespace Ghurund {
    class Shaders {
    private:
        Shaders() = delete;

    public:
        static Shader* loadBasic(ResourceContext& context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/basic.hlsl");
        }

        static Shader* loadBasicLight(ResourceContext& context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/basicLight.hlsl");
        }

        static Shader* loadToon(ResourceContext& context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/toon.hlsl");
        }

        static Shader* loadWireframe(ResourceContext & context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/wireframe.hlsl");
        }

        static Shader* loadOutline(ResourceContext & context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/outline.hlsl");
        }

        static Shader* loadNormals(ResourceContext & context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/normals.hlsl");
        }

        static Shader* loadInvalid(ResourceContext & context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/invalid.hlsl");
        }

        static Shader* loadLightPass(ResourceContext & context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/lightPass.hlsl");
        }

        static Shader* loadUi(ResourceContext & context) {
            return context.ResourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/ui.hlsl");
        }
    };
}