#pragma once

#include "ui/image/Bitmap.h"

namespace UnitTest {
    using namespace Ghurund::Core;

    class TestBitmap:public Ghurund::UI::Bitmap {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<TestBitmap>(UnitTest::NAMESPACE_NAME, "TestBitmap")
                .withSupertype(__super::GET_TYPE());

            return GET_TYPE();
        }

        inline static const Ghurund::Core::Type& TYPE = Bitmap::GET_TYPE();
#pragma endregion

    public:
        virtual Ghurund::Core::IntSize getSize() const override {
            return {};
        }

        __declspec(property(get = getSize)) Ghurund::Core::IntSize Size;
    };

}