#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/TestClass.h"
#include "test/MemoryGuard.h"

#include "core/string/TextConversionUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::AString>(const Ghurund::Core::AString& t) {
        return convertText<char, wchar_t>(t).Data;
    }
}

namespace UnitTest {
    using namespace UnitTest::Utils;

    TEST_CLASS(PropertyTest) {
public:

    TEST_METHOD(readOnlyProperty_uint32) {
        getType<ObjectTestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            MemoryGuard guard;
            {
                ObjectTestClass testObj;
                size_t index = testObj.Type.Properties.find([](const BaseProperty& obj) { return obj.Name == "val"; });
                auto& valProperty = (Property<ObjectTestClass, uint32_t>&)testObj.Type.Properties[index].get();
                Assert::IsTrue(valProperty.CanRead);
                Assert::IsFalse(valProperty.CanWrite);

                testObj.val = 5u;
                uint32_t val = valProperty.get(testObj);
                Assert::AreEqual(5u, val);
            }
        }
    }

    TEST_METHOD(property_charPointer) {
        getType<ObjectTestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            MemoryGuard guard;
            {
                ObjectTestClass testObj;
                size_t index = testObj.Type.Properties.find([](const BaseProperty& obj) { return obj.Name == "text"; });
                auto& textProperty = (const Property<ObjectTestClass, const char*>&)testObj.Type.Properties[index].get();

                testObj.setText("lemon");
                const char* text = textProperty.get(testObj);
                Assert::AreEqual("lemon", text);

                textProperty.set(testObj, "apple");
                Assert::AreEqual("apple", testObj.getText());
            }
        }
    }

    TEST_METHOD(writeOnlyProperty_float) {
        getType<ObjectTestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            MemoryGuard guard;
            {
                ObjectTestClass testObj;
                size_t index = testObj.Type.Properties.find([](const BaseProperty& obj) { return obj.Name == "progress"; });
                auto& progressProperty = (Property<ObjectTestClass, float>&)testObj.Type.Properties[index].get();
                Assert::IsFalse(progressProperty.CanRead);
                Assert::IsTrue(progressProperty.CanWrite);

                testObj.progress = 0.5f;
                progressProperty.set(testObj, 0.3f);
                Assert::AreEqual(0.3f, testObj.progress);
            }
        }
    }

    TEST_METHOD(findPropertyByType) {
        getType<ObjectTestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            MemoryGuard guard;
            {
                ObjectTestClass testObj;
                size_t progressIndex = testObj.Type.Properties.find([](const BaseProperty& obj) { return obj.Name == "progress"; });
                size_t floatIndex = testObj.Type.Properties.find([](const BaseProperty& obj) { return obj.Type == getType<float>(); });
                Assert::AreEqual(progressIndex, floatIndex);
                Assert::AreNotEqual(testObj.Type.Properties.Size, floatIndex);
            }
        }
    }

    TEST_METHOD(templateProperty) {
        getType<ObjectTestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            MemoryGuard guard;
            {
                ObjectTestClass testObj;
                size_t observableIndex = testObj.Type.Properties.find([](const BaseProperty& obj) { return obj.Type.Name.startsWith("Observable"); });
                const BaseProperty& observableProperty = testObj.Type.Properties[observableIndex];
                observableProperty.getRaw(&testObj, [&](void* val) {
                    Assert::IsNotNull(val);

                    Object* observable = (Object*)val;
                    size_t valueIndex = observable->Type.Properties.find([](const BaseProperty& obj) { return obj.Name == "Value"; });
                    const BaseProperty& valueProperty = observable->Type.Properties[valueIndex];
                    Ghurund::Core::AString value;
                    valueProperty.getRaw(val, [&](void* val) {
                        value = *(Ghurund::Core::AString*)val;
                    });
                    Assert::AreEqual(testObj.name.Value, value);
                });
            }
        }
    }

    TEST_METHOD(templateMethod) {
        getType<ObjectTestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            MemoryGuard guard;
            {
                ObjectTestClass testObj;
                size_t observableIndex = testObj.Type.Properties.find([](const BaseProperty& obj) { return obj.Type.Name.startsWith("Observable"); });
                const BaseProperty& observableProperty = testObj.Type.Properties[observableIndex];
                Object* observable = nullptr;
                observableProperty.getRaw(&testObj, [&](void* val) { observable = (Object*)val; });
                Assert::IsNotNull(observable);

                size_t addIndex = observable->Type.Methods.find([](const BaseMethod& obj) { return obj.Name == "add"; });
                const BaseMethod& addMethod = observable->Type.Methods[addIndex];
                SharedPointer<ObservableHandler<AString>> handler = ghnew ObservableHandler<AString>([](const AString& f) {});
                addMethod.invokeRaw<SharedPointer<ObservableHandler<AString>>>(observable, handler);
            }
        }
    }
    };
}
