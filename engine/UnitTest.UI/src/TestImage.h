#pragma once

#include "ui/drawable/ImageDrawable.h"

namespace UnitTest {
    using namespace Ghurund::UI;

    class TestImage:public ImageDrawable {
    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<ImageDrawable>(Ghurund::UI::NAMESPACE_NAME, "ImageDrawable")
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

    public:
        inline void setPreferredSize(const FloatSize& size) {
            preferredSize = size;
        }

        virtual void onDraw(ICanvas& canvas) override {}
    };
}