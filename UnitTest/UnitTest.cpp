#include "pch.h"
#include "CppUnitTest.h"

#include "Ghurund.h"
#include "core/string/String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;

    TEST_CLASS(StringTest) {
public:

    TEST_METHOD(TestString) {
        UnicodeString str = "test str";
        Assert::AreEqual(str.Size, (size_t)9);
        Assert::AreEqual(str.Length, (size_t)8);

        str.add("add");
        Assert::AreEqual(str.getData(), L"test stradd");

        str.add(L"add2");
        Assert::AreEqual(str.getData(), L"test straddadd2");

        str.add('a');
        Assert::AreEqual(str.getData(), L"test straddadd2a");
    }
    };
}
