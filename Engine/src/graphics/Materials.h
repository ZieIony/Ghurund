#pragma once

#include "Material.h"
#include "shader/Shaders.h"
#include "texture/Textures.h"

namespace Ghurund {
    class Materials {
    private:
        Materials() = delete;

        static Material* makeWithShader(Shader *shader, ResourceContext& context);

    public:
        static Material* makeBasic(ResourceManager& resourceManager, ResourceContext& context, Texture& texture);

        static Material* makeBasicLight(ResourceManager& resourceManager, ResourceContext& context, Texture& diffuseTexture, Texture& specularTexture);

        static Material* makeToon(ResourceManager& resourceManager, ResourceContext& context, Texture& texture);

        static Material* makeChecker(ResourceManager& resourceManager, ResourceContext& context);

        static Material* makeWireframe(ResourceManager& resourceManager, ResourceContext& context);

        static Material* makeOutline(ResourceManager& resourceManager, ResourceContext& context);

        static Material* makeNormals(ResourceManager& resourceManager, ResourceContext& context);

        static Material* makeInvalid(ResourceManager& resourceManager, ResourceContext& context);

        static Material* makeLightPass(ResourceManager& resourceManager, ResourceContext& context);
    };
}