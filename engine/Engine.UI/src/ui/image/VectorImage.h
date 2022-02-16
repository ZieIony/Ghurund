#pragma once

#include "core/math/Size.h"
#include "core/resource/Resource.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class VectorImage:public Ghurund::Core::Resource {
    public:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

    public:
        virtual Ghurund::Core::FloatSize getSize() const = 0;

        __declspec(property(get = getSize)) Ghurund::Core::FloatSize Size;
    };
}