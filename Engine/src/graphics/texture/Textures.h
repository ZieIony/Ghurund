#pragma once

#include "Texture.h"
#include "core/SharedPointer.h"

namespace Ghurund {
    class Textures {
    private:
        Textures() = delete;

        static Texture* make(ResourceContext& context, const wchar_t* fileName) {
            auto path = fmt::format(L"{}{}{}", ResourceManager::LIB_PROTOCOL_PREFIX, ResourceManager::ENGINE_LIB_NAME, fileName).c_str();
            return makeFromImage(context, FilePath(path));
        }

    public:
        static Texture* makeDefaultDiffuse(ResourceContext& context) {
            return make(context, L"/textures/diffuse.png");
        }

        static Texture* makeDefaultSpecular(ResourceContext& context) {
            return make(context, L"/textures/specular.png");
        }

        static Texture* makeDefaultNormal(ResourceContext& context) {
            return make(context, L"/textures/normal.png");
        }

        static Texture* makeChecker(ResourceContext& context) {
            return make(context, L"/textures/checker.png");
        }

        static Texture* makeFromImage(ResourceContext& context, const FilePath& imagePath) {
            Image* image = context.ResourceManager.load<Image>(context, imagePath);
            if (image == nullptr)
                return nullptr;
            Texture* texture = ghnew Texture();
            texture->init(context, *image);
            image->release();
            return texture;
        }
    };
}