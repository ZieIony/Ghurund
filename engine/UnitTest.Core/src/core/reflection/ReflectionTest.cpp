#include "pch.h"
#include "CppUnitTest.h"
#include "TestUtils.h"

#include "TestClass.h"
#include "MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::AString>(const Ghurund::Core::AString& t) {
        return convertText<char, wchar_t>(t).Data;
    }
}

namespace UnitTest {
    TEST_CLASS(ReflectionTest) {
public:

    TEST_METHOD(readOnlyProperty_uint32) {
        MemoryGuard guard;
        {
            UnitTest::TestClass testObj;
            size_t index = testObj.Type.Properties.find([](const BaseProperty* obj) { return obj->Name == "val"; });
            auto valProperty = (ReadOnlyProperty<UnitTest::TestClass, uint32_t>*)testObj.Type.Properties[index];

            testObj.val = 5u;
            uint32_t val = valProperty->get(testObj);
            Assert::AreEqual(5u, val);
        }
    }

    TEST_METHOD(property_charPointer) {
        MemoryGuard guard;
        {
            UnitTest::TestClass testObj;
            size_t index = testObj.Type.Properties.find([](const BaseProperty* obj) { return obj->Name == "text"; });
            auto textProperty = (Property<UnitTest::TestClass, const char*>*)testObj.Type.Properties[index];

            testObj.setText("lemon");
            const char* text = textProperty->get(testObj);
            Assert::AreEqual("lemon", text);

            textProperty->set(testObj, "apple");
            Assert::AreEqual("apple", testObj.getText());
        }
    }

    TEST_METHOD(writeOnlyProperty_float) {
        MemoryGuard guard;
        {
            UnitTest::TestClass testObj;
            size_t index = testObj.Type.Properties.find([](const BaseProperty* obj) { return obj->Name == "progress"; });
            auto progressProperty = (WriteOnlyProperty<UnitTest::TestClass, float>*)testObj.Type.Properties[index];

            testObj.progress = 0.5f;
            progressProperty->set(testObj, 0.3f);
            Assert::AreEqual(0.3f, testObj.progress);
        }
    }

    TEST_METHOD(findPropertyByType) {
        MemoryGuard guard;
        {
            UnitTest::TestClass testObj;
            size_t progressIndex = testObj.Type.Properties.find([](const BaseProperty* obj) { return obj->Name == "progress"; });
            size_t floatIndex = testObj.Type.Properties.find([](const BaseProperty* obj) { return obj->Type == getType<float>(); });
            Assert::AreEqual(progressIndex, floatIndex);
            Assert::AreNotEqual(testObj.Type.Properties.Size, floatIndex);
        }
    }

    TEST_METHOD(templateProperty) {
        MemoryGuard guard;
        {
            UnitTest::TestClass testObj;
            size_t observableIndex = testObj.Type.Properties.find([](const BaseProperty* obj) { return obj->Type.Name.startsWith("Observable"); });
            auto observableProperty = testObj.Type.Properties[observableIndex];
            observableProperty->getRaw(&testObj, [&](void* val) {
                Assert::IsNotNull(val);

                Object* observable = (Object*)val;
                size_t valueIndex = observable->Type.Properties.find([](const BaseProperty* obj) { return obj->Name == "Value"; });
                auto valueProperty = observable->Type.Properties[valueIndex];
                Ghurund::Core::AString value;
                valueProperty->getRaw(val, [&](void* val) {
                    value = *(Ghurund::Core::AString*)val;
                });
                Assert::AreEqual(testObj.name.Value, value);
            });
        }
    }

    TEST_METHOD(templateMethod) {
        MemoryGuard guard;
        {
            UnitTest::TestClass testObj;
            size_t observableIndex = testObj.Type.Properties.find([](const BaseProperty* obj) { return obj->Type.Name.startsWith("Observable"); });
            auto observableProperty = testObj.Type.Properties[observableIndex];
            Object* observable = nullptr;
            observableProperty->getRaw(&testObj, [&](void* val) { observable = (Object*)val; });
            Assert::IsNotNull(observable);

            size_t addIndex = observable->Type.Methods.find([](const BaseMethod* obj) { return obj->Name == "add"; });
            auto addMethod = observable->Type.Methods[addIndex];
            //addMethod->invoke(
        }
    }
    };
}
