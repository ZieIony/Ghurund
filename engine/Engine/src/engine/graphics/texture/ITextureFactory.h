#pragma once

#include "core/object/Noncopyable.h"
#include "ITexture.h"
#include <core/image/Image.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ITextureFactory:public Noncopyable {
    public:
        virtual ITexture* makeTexture(Image& image) = 0;
    };
}