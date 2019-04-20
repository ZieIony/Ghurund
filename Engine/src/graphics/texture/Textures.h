#pragma once

#include "Texture.h"

namespace Ghurund {
    class Textures {
    private:
        Textures() = delete;

    public:
        static Texture* makeChecker(ResourceManager& resourceManager, ResourceContext& context) {
            Image* image = resourceManager.load<Image>(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/textures/checker.png");
            Texture * texture = ghnew Texture();
            texture->init(context, *image);
            image->release();
            return texture;
        }
    };
}