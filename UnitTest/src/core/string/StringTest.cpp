#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/Tree.h"
#include "core/string/String.h"
#include "TestUtils.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;

    TEST_CLASS(StringTest) {
public:

    TEST_METHOD(String_size) {
        WString str = L"test str";
        Assert::AreEqual(str.Size, (size_t)9);
        Assert::AreEqual(str.Length, (size_t)8);

        str.add(L"add");
        Assert::AreEqual(str.getData(), L"test stradd");

        str.add('a');
        Assert::AreEqual(str.getData(), L"test stradda");
    }

    TEST_METHOD(String_order) {
        Tree<WString> names = { L"Pawe³", L"Piotr", L"Leokadia", L"Magda", L"Zuzia", L"Marcel", L"Burek", L"test" };
        std::vector<WString> sortedNames = { L"Burek", L"Leokadia", L"Magda", L"Marcel", L"Pawe³", L"Piotr", L"test", L"Zuzia" };

        Assert::IsTrue(collectionsEqual(names, sortedNames));
    }
    };
}
