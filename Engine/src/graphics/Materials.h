#pragma once

#include "Material.h"
#include "shader/Shaders.h"
#include "texture/Textures.h"

namespace Ghurund {
    class Materials {
    private:
        Materials() = delete;

    public:
        static Material *makeChecker(ResourceManager &resourceManager, ResourceContext &context);

        static Material *makeWireframe(ResourceManager &resourceManager, ResourceContext &context);

        static Material *makeNormals(ResourceManager &resourceManager, ResourceContext &context);

        static Material *makeInvalid(ResourceManager &resourceManager, ResourceContext &context);
    };
}