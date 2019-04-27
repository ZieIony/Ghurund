#pragma once

#include "Texture.h"
#include "core/ScopedPointer.h"

namespace Ghurund {
    class Textures {
    private:
        Textures() = delete;

    public:
        static Texture* makeChecker(ResourceManager& resourceManager, ResourceContext& context) {
            return makeFromImage(resourceManager, context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/textures/checker.png");
        }

        static Texture* makeFromImage(ResourceManager& resourceManager, ResourceContext& context, const FilePath& imagePath) {
            ScopedPointer<Image> image = resourceManager.load<Image>(context, imagePath);
            if (image == nullptr)
                return nullptr;
            Texture* texture = ghnew Texture();
            texture->init(context, *image);
            return texture;
        }
    };
}