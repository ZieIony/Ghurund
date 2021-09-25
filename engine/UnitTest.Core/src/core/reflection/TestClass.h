#pragma once

#include "core/Object.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

namespace UnitTest {
    using namespace Ghurund::Core;

    class TestClass:public Object {
    private:
        uint32_t val = 5;
        char* text = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Constructor<TestClass>();
            static const auto CONSTRUCTOR2 = Constructor<TestClass, uint32_t>();
            static const auto valProp = ReadOnlyProperty<TestClass, uint32_t>("val", &getVal);
            static const auto textProp = Property<TestClass, const char*>("text", &getText, &setText);
            static const Ghurund::Core::Type TYPE = TypeBuilder<TestClass>(NAMESPACE_NAME, GH_STRINGIFY(TestClass))
                .withConstructor(CONSTRUCTOR)
                .withConstructor(CONSTRUCTOR2)
                .withSupertype(__super::GET_TYPE())
                .withProperty(valProp)
                .withProperty(textProp);

            return TYPE;
        }

    public:
        TestClass() {}

        TestClass(uint32_t val):val(val) {}

        uint32_t getVal() const {
            return val;
        }

        const char* getText() const {
            return text;
        }

        void setText(const char* text) {
            //strcpy(this->text, text);
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const {
            return TYPE;
        }
    };
}
