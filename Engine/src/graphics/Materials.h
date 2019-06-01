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
        static Material* makeBasic(ResourceContext& context, Texture* texture = nullptr);

        static Material* makeBasicLight(ResourceContext& context, Texture* diffuseTexture = nullptr, Texture* specularTexture = nullptr);

        static Material* makeToon(ResourceContext& context, Texture* texture = nullptr);

        static Material* makeChecker(ResourceContext& context);

        static Material* makeWireframe(ResourceContext& context);

        static Material* makeOutline(ResourceContext& context);

        static Material* makeNormals(ResourceContext& context);

        static Material* makeInvalid(ResourceContext& context);

        static Material* makeLightPass(ResourceContext& context);

        static Material* makeUi(ResourceContext& context);
    };
}