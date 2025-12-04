#pragma once

#include "ITexture.h"
#include "core/object/Noncopyable.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ITextureProvider:public Noncopyable {
    public:
        virtual ITexture* makeDefaultDiffuse() const = 0;

        virtual ITexture* makeDefaultSpecular() const = 0;

        virtual ITexture* makeDefaultNormal() const = 0;

        virtual ITexture* makeChecker() const = 0;

        virtual ITexture* makeFromImage(const ResourcePath& imagePath) const = 0;
    };
}