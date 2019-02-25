#pragma once

#include "Texture.h"

namespace Ghurund {
    class Textures {
    private:
        Textures() = delete;

    public:
        static Texture *makeChecker(ResourceManager &resourceManager, ResourceContext &context) {
            Image *image = resourceManager.load<Image>(context, "textures/checker.png");
            Texture *texture = ghnew Texture();
            texture->init(context, *image);
            return texture;
        }
    };
}