#pragma once

#include "core/math/Size.h"
#include "core/resource/Resource.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Bitmap:public Ghurund::Core::Resource {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

    public:
        virtual Ghurund::Core::IntSize getSize() const = 0;

        __declspec(property(get = getSize)) Ghurund::Core::IntSize Size;
    };
}