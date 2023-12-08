#pragma once

#include "core/Pointer.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"
#include "core/Observable.h"

#include <stdint.h>

namespace UnitTest::Utils {
    using namespace Ghurund::Core;

    struct SimpleTestClass {
        uint32_t val = 5;
        const char* text = "text";
    };

    class PointerTestClass:public Pointer {};

    class ObjectTestClass:public Object {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Constructor<ObjectTestClass>();
            static const auto CONSTRUCTOR2 = Constructor<ObjectTestClass, uint32_t>();

            static const auto valProp = Property<ObjectTestClass, uint32_t>("val", &getVal);
            static const auto textProp = Property<ObjectTestClass, const char*>("text", &getText, &setText);
            static const auto writeProp = Property<ObjectTestClass, float>("progress", &setProgress);
            static const auto observableProp = Property<ObjectTestClass, Observable<Ghurund::Core::AString>&>("name", [](ObjectTestClass& obj)->Observable<AString>& {return obj.name; });

            static const Ghurund::Core::Type TYPE = TypeBuilder<ObjectTestClass>("UnitTest::Utils", GH_STRINGIFY(ObjectTestClass))
                .withConstructor(CONSTRUCTOR)
                .withConstructor(CONSTRUCTOR2)
                .withSupertype(__super::GET_TYPE())
                .withProperty(valProp)
                .withProperty(textProp)
                .withProperty(writeProp)
                .withProperty(observableProp);

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = ObjectTestClass::GET_TYPE();
#pragma endregion

    public:
        uint32_t val = 5;
        char* text = nullptr;
        float progress = 0.1f;

        Observable<Ghurund::Core::AString> name = Ghurund::Core::AString("Jake");

        ObjectTestClass() {}

        ObjectTestClass(uint32_t val):val(val) {}

        ~ObjectTestClass() {
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
    };
}