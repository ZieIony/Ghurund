#pragma once

#include "Material.h"
#include "shader/Shaders.h"
#include "texture/Textures.h"

namespace Ghurund {
    class Materials {
    private:
        Materials() = delete;

    public:
        static Material *loadChecker(ResourceManager &resourceManager, ResourceContext &context) {
            Shader *shader = Shaders::loadBasic(resourceManager, context);
            Material *material = ghnew Material(shader);
            Texture *texture = Textures::loadChecker(resourceManager, context);
            material->Textures.set("diffuse", texture);
            shader->release();
            return material;
        }

        static Material *loadWireframe(ResourceManager &resourceManager, ResourceContext &context) {
            Shader *shader = Shaders::loadWireframe(resourceManager, context);
            Material *material = ghnew Material(shader);
            shader->release();
            return material;
        }
    };
}