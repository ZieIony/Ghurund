#pragma once

#include "ITexture.h"

#include "core/object/Noncopyable.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class TextureProvider:public Noncopyable {
    public:
        virtual ITexture* makeDefaultDiffuse() const = 0;

        virtual ITexture* makeDefaultSpecular() const = 0;

        virtual ITexture* makeDefaultNormal() const = 0;

        virtual ITexture* makeChecker() const = 0;
	};
}