#pragma once

#include "ui/drawable/ImageDrawable.h"

namespace UnitTest {
    using namespace Ghurund::UI;

    class TestImage:public ImageDrawable {
    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<ImageDrawable>(Ghurund::UI::NAMESPACE_NAME, "ImageDrawable")
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

    public:
        inline void setPreferredSize(const FloatSize& size) {
            preferredSize = size;
        }

        virtual void onDraw(ICanvas& canvas) override {}
    };
}