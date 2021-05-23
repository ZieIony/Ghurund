#include "pch.h"
#include "CppUnitTest.h"

#include "core/TypeWrapper.h"
#include <core/string/String.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;

    class Username:public TypeWrapper<String> {};
    class Password:public TypeWrapper<String> {};

    TEST_CLASS(TypeWrapperTest) {
public:

    TEST_METHOD(TypeWrapper_equality) {
        {
            Username username = Username(WString(L"test"));
            Username username2 = Username(WString(L"test2"));
            Password password = Password(WString(L"test"));
            Password password2 = Password(WString(L"test"));

            WString& str = username;
            const WString& str2 = username;

            Assert::AreNotEqual(username, username2);
            Assert::AreEqual(password, password2);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(TypeWrapper_conversions) {
        {
            Assert::IsFalse(std::is_convertible<WString, Username>::value);
            Assert::IsFalse(std::is_convertible<WString, Password>::value);
            Assert::IsFalse(std::is_convertible<Username, Password>::value);
            Assert::IsFalse(std::is_convertible<Password, Username>::value);
            Assert::IsFalse(std::is_constructible<TypeWrapper<String>>::value);
        }
        _____________________checkMemory();
    }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<UnitTest::Username>(const UnitTest::Username& t) {
        return t.Value.Data;
    }

    template<> static std::wstring ToString<UnitTest::Password>(const UnitTest::Password& t) {
        return t.Value.Data;
    }
}
