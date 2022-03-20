#pragma once

#include "ui/image/Bitmap.h"

namespace UnitTest {

    class Bitmap:public Ghurund::UI::Bitmap {
    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<ImageDrawable>(UnitTest::NAMESPACE_NAME, "Bitmap")
                .withSupertype(__super::GET_TYPE());

            return GET_TYPE();
        }

    public:
        

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

    public:
        virtual Ghurund::Core::IntSize getSize() const override {
            return {};
        }

        __declspec(property(get = getSize)) Ghurund::Core::IntSize Size;
    };

}