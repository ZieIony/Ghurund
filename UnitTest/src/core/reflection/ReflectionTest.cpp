#include "pch.h"
#include "CppUnitTest.h"

#include "core/Object.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;

    class TestClass:public Object {
    private:
        uint32_t val = 5;
        char* text = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<TestClass>();
            static const auto valProp = UInt32Property<TestClass>("val", &getVal);
            static const auto textProp = TypedProperty<TestClass, const char*>("string", "text", &getText, &setText);
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TestClass))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE())
                .withProperty(valProp)
                .withProperty(textProp, "group");

            return TYPE;
        }

    public:
        uint32_t getVal() const {
            return val;
        }

        const char* getText() const {
            return text;
        }

        void setText(const char *text) {
            //strcpy(this->text, text);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const {
            return TYPE;
        }
    };

    TEST_CLASS(ReflectionTest) {
public:

    TEST_METHOD(reflection) {
        TestClass testObj;
        _____________________checkMemory();
    }
    };
}
