#pragma once

#include "ui/drawable/Drawable.h"

namespace UnitTest {
    using namespace Ghurund::UI;

    class TestImage:public Drawable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<TestImage>()
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = TestImage::GET_TYPE();
#pragma endregion

    public:
        inline void setPreferredSize(const FloatSize& size) {
            preferredSize = size;
        }

        virtual void draw(RenderGroup& group, const Ghurund::Core::FloatSize& size, const Ghurund::UI::Color& tint) const {}
    };
}