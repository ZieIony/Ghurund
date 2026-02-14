#pragma once

#include "ITexture.h"

#include "core/image/Image.h"
#include "core/object/Noncopyable.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ITextureFactory:public Noncopyable {
    public:
        virtual ITexture* makeTexture(Image& image, TextureType textureType) = 0;
    };
}