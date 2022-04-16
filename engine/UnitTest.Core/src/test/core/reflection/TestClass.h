#pragma once

#include "core/Object.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"
#include "core/Observable.h"

namespace UnitTest {
    using namespace Ghurund::Core;

    class TestClass:public Object {
    public:
        uint32_t val = 5;
        char* text = nullptr;
        float progress = 0.1f;

        Observable<Ghurund::Core::AString> name = Ghurund::Core::AString("Jake");

        TestClass() {}

        TestClass(uint32_t val):val(val) {}

        ~TestClass() {
            delete[] text;
        }

        inline uint32_t getVal() const {
            return val;
        }

        inline const char* getText() const {
            return text;
        }

        inline void setText(const char* text) {
            delete this->text;
            this->text = copyStr(text);
        }

        inline void setProgress(const float p) {
            this->progress = p;
        }

        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Constructor<TestClass>();
            static const auto CONSTRUCTOR2 = Constructor<TestClass, uint32_t>();

            static const auto valProp = Property<TestClass, uint32_t>("val", &getVal);
            static const auto textProp = Property<TestClass, const char*>("text", &getText, &setText);
            static const auto writeProp = Property<TestClass, float>("progress", &setProgress);
            static const auto observableProp = Property<TestClass, Observable<Ghurund::Core::AString>&>("name", [](TestClass& obj)->Observable<AString>& {return obj.name; });

            static const Ghurund::Core::Type TYPE = TypeBuilder<TestClass>("UnitTest::Utils", GH_STRINGIFY(TestClass))
                .withConstructor(CONSTRUCTOR)
                .withConstructor(CONSTRUCTOR2)
                .withSupertype(__super::GET_TYPE())
                .withProperty(valProp)
                .withProperty(textProp)
                .withProperty(writeProp)
                .withProperty(observableProp);

            return TYPE;
        }

        virtual const Ghurund::Core::Type& getType() const {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}
