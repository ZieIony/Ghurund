#pragma once

#include "graphics/shader/Shader.h"

namespace Ghurund {
    class Shaders {
    private:
        Shaders() = delete;

    public:
        static Shader *loadBasic(ResourceManager &resourceManager, ResourceContext &context) {
            return resourceManager.load<Shader>(context, "shaders/basic.hlsl");
        }

        static Shader *loadWireframe(ResourceManager &resourceManager, ResourceContext &context) {
            return resourceManager.load<Shader>(context, "shaders/wireframe.hlsl");
        }

        static Shader *loadNormals(ResourceManager &resourceManager, ResourceContext &context) {
            return resourceManager.load<Shader>(context, "shaders/normals.hlsl");
        }

        static Shader *loadInvalid(ResourceManager &resourceManager, ResourceContext &context) {
            return resourceManager.load<Shader>(context, "shaders/invalid.hlsl");
        }

        static Shader *loadLightPass(ResourceManager &resourceManager, ResourceContext &context) {
            return resourceManager.load<Shader>(context, "shaders/lightPass.hlsl");
        }
    };
}