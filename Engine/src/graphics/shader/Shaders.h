#pragma once

#include "graphics/shader/Shader.h"

namespace Ghurund {
    class Shaders {
    private:
        Shaders() = delete;

    public:
        static Shader* loadBasic(ResourceManager& resourceManager, ResourceContext& context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/basic.hlsl");
        }

        static Shader* loadBasicLight(ResourceManager& resourceManager, ResourceContext& context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/basicLight.hlsl");
        }

        static Shader* loadToon(ResourceManager& resourceManager, ResourceContext& context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/toon.hlsl");
        }

        static Shader* loadWireframe(ResourceManager & resourceManager, ResourceContext & context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/wireframe.hlsl");
        }

        static Shader* loadOutline(ResourceManager & resourceManager, ResourceContext & context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/outline.hlsl");
        }

        static Shader* loadNormals(ResourceManager & resourceManager, ResourceContext & context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/normals.hlsl");
        }

        static Shader* loadInvalid(ResourceManager & resourceManager, ResourceContext & context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/invalid.hlsl");
        }

        static Shader* loadLightPass(ResourceManager & resourceManager, ResourceContext & context) {
            return resourceManager.load<Shader>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/shaders/lightPass.hlsl");
        }
    };
}