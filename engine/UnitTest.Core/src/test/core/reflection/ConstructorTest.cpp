#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"

#include "TestClass.h"
#include "test/MemoryGuard.h"
#include "core/string/TextConversionUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::AString>(const Ghurund::Core::AString& t) {
        return convertText<char, wchar_t>(t).Data;
    }
}

namespace UnitTest {
    TEST_CLASS(ConstructorTest) {
public:

    TEST_METHOD(Constructor_findBySignature) {
        getType<UnitTest::TestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            Utils::MemoryGuard guard;
            {
                const BaseConstructor* constructor = getType<UnitTest::TestClass>().Constructors.findBySignature<uint32_t>();
                UnitTest::TestClass* obj = (UnitTest::TestClass*)constructor->invokeRaw(6u);
                Assert::IsNotNull(obj);
                Assert::AreEqual(6u, obj->val);
                delete obj;
            }
        }
    }

    TEST_METHOD(Constructor_findNoArgs) {
        getType<UnitTest::TestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            Utils::MemoryGuard guard;
            {
                const BaseConstructor* constructor = getType<UnitTest::TestClass>().Constructors.findBySignature<>();
                UnitTest::TestClass* obj = (UnitTest::TestClass*)constructor->invokeRaw();
                Assert::IsNotNull(obj);
                Assert::AreEqual(5u, obj->val);
                delete obj;
            }
        }
    }

    TEST_METHOD(Constructor_findNoConstructor) {
        getType<UnitTest::TestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<const uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            Utils::MemoryGuard guard;
            {
                const BaseConstructor* constructor = getType<UnitTest::TestClass>().Constructors.findBySignature<const uint32_t>();
                Assert::IsNull(constructor);
            }
        }
    }

    TEST_METHOD(Constructor_invalidInvoke) {
        getType<UnitTest::TestClass>();
        getType<float>();
        getType<const char*>();
        getType<uint32_t>();
        getType<Observable<Ghurund::Core::AString>&>();
        {
            Utils::MemoryGuard guard;
            {
                const BaseConstructor* constructor = getType<UnitTest::TestClass>().Constructors.findBySignature<uint32_t>();
                Assert::ExpectException<InvalidParamException>([&] {
                    UnitTest::TestClass* obj = (UnitTest::TestClass*)constructor->invokeRaw(1.0f);
                });
            }
        }
    }
    };
}
