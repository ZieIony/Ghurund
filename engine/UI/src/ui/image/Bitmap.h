#pragma once

#include "core/math/Size.h"
#include "core/resource/Resource.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Bitmap:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Bitmap::GET_TYPE();
#pragma endregion

    public:
        virtual Ghurund::Core::IntSize getSize() const = 0;

        __declspec(property(get = getSize)) Ghurund::Core::IntSize Size;
    };
}