#pragma once

#include "ITexture.h"

namespace Ghurund::Engine {
    class ITextureProvider {
    public:
        virtual ITexture* makeDefaultDiffuse() const = 0;

        virtual ITexture* makeDefaultSpecular() const = 0;

        virtual ITexture* makeDefaultNormal() const = 0;

        virtual ITexture* makeChecker() const = 0;

        virtual ITexture* makeFromImage(const ResourcePath& imagePath) const = 0;
    };
}