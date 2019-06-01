#pragma once

#include "Texture.h"
#include "core/ScopedPointer.h"

namespace Ghurund {
    class Textures {
    private:
        Textures() = delete;

    public:
        static Texture* makeDefaultDiffuse(ResourceContext& context) {
            return makeFromImage(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/textures/diffuse.png");
        }

        static Texture* makeDefaultSpecular(ResourceContext& context) {
            return makeFromImage(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/textures/specular.png");
        }

        static Texture* makeDefaultNormal(ResourceContext& context) {
            return makeFromImage(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/textures/normal.png");
        }

        static Texture* makeChecker(ResourceContext& context) {
            return makeFromImage(context, U(ResourceManager::LIB_PROTOCOL_PREFIX) + ResourceManager::ENGINE_LIB_NAME + "/textures/checker.png");
        }

        static Texture* makeFromImage(ResourceContext& context, const FilePath& imagePath) {
            ScopedPointer<Image> image = context.ResourceManager.load<Image>(context, imagePath);
            if (image == nullptr)
                return nullptr;
            Texture* texture = ghnew Texture();
            texture->init(context, *image);
            return texture;
        }
    };
}