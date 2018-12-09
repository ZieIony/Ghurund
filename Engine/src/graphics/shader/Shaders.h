#pragma once

#include "graphics/shader/Shader.h"

namespace Ghurund {
    class Shaders {
    private:
        Shaders() = delete;

    public:
        static Shader *loadBasic(ResourceManager &resourceManager, ResourceContext &context) {
            return resourceManager.load<Shader>(context, "../shaders/basic.hlsl");
        }

        static Shader *loadWireframe(ResourceManager &resourceManager, ResourceContext &context) {
            Shader *shader = resourceManager.load<Shader>(context, "../shaders/wireframe.hlsl");
            shader->makePipelineState(true);
            return shader;
        }

        static Shader *loadNormals(ResourceManager &resourceManager, ResourceContext &context) {
            return resourceManager.load<Shader>(context, "../shaders/normals.hlsl");
        }
    };
}