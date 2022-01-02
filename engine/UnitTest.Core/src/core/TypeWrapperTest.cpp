#include "pch.h"
#include "CppUnitTest.h"
#include "MemoryGuard.h"

#include "core/TypeWrapper.h"
#include <core/string/String.h>
#include <core/string/TextConversionUtils.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;

    class Username:public TypeWrapper<String> {};
    class Password:public TypeWrapper<String> {};

    TEST_CLASS(TypeWrapperTest) {
    public:

        TEST_METHOD(TypeWrapper_equality) {
            MemoryGuard guard;
            {
                Username username = Username(String(_T("test")));
                Username username2 = Username(String(_T("test2")));
                Password password = Password(String(_T("test")));
                Password password2 = Password(String(_T("test")));

                String& str = username;
                const String& str2 = username;

                Assert::AreNotEqual(username, username2);
                Assert::AreEqual(password, password2);
            }
        }

        TEST_METHOD(TypeWrapper_conversions) {
            MemoryGuard guard;
            {
                Assert::IsFalse(std::is_convertible<WString, Username>::value);
                Assert::IsFalse(std::is_convertible<WString, Password>::value);
                Assert::IsFalse(std::is_convertible<Username, Password>::value);
                Assert::IsFalse(std::is_convertible<Password, Username>::value);
                Assert::IsFalse(std::is_constructible<TypeWrapper<String>>::value);
            }
        }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<UnitTest::Username>(const UnitTest::Username& t) {
        return convertText<tchar, wchar_t>(t.Value).Data;
    }

    template<> static std::wstring ToString<UnitTest::Password>(const UnitTest::Password& t) {
        return convertText<tchar, wchar_t>(t.Value).Data;
    }
}
