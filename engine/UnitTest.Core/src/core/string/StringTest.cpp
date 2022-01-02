#include "pch.h"
#include "CppUnitTest.h"
#include "TestUtils.h"
#include "MemoryGuard.h"

#include "core/collection/Tree.h"
#include "core/string/String.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;

    TEST_CLASS(StringTest) {
public:

    TEST_METHOD(String_size) {
        MemoryGuard guard;
        {
            WString str = L"test str";
            Assert::AreEqual(str.Size, (size_t)9);
            Assert::AreEqual(str.Length, (size_t)8);

            str.add(L"add");
            Assert::AreEqual(str.getData(), L"test stradd");

            str.add('a');
            Assert::AreEqual(str.getData(), L"test stradda");
        }
    }

    TEST_METHOD(String_order) {
        MemoryGuard guard;
        {
            Tree<WString> names = { L"Pawe³", L"Piotr", L"Leokadia", L"Magda", L"Zuzia", L"Marcel", L"Burek", L"test" };
            std::vector<WString> sortedNames = { L"Burek", L"Leokadia", L"Magda", L"Marcel", L"Pawe³", L"Piotr", L"test", L"Zuzia" };

            Assert::IsTrue(collectionsEqual(names, sortedNames));
        }
    }

    TEST_METHOD(String_replace) {
        MemoryGuard guard;
        {
            WString testStr = L"test text with test words to test string replace";

            WString replacedText = WString(testStr);
            replacedText.replace(L"test", L"plum");
            Assert::AreEqual(L"plum text with plum words to plum string replace", replacedText.Data);

            WString replacedText2 = WString(testStr);
            replacedText2.replace(L"test", L"lemon");
            Assert::AreEqual(L"lemon text with lemon words to lemon string replace", replacedText2.Data);

            WString replacedText3 = WString(testStr);
            replacedText3.replace(L"test", L"a");
            Assert::AreEqual(L"a text with a words to a string replace", replacedText3.Data);

            WString replacedText4 = WString(testStr);
            replacedText4.replace(L' ', L'_');
            Assert::AreEqual(L"test_text_with_test_words_to_test_string_replace", replacedText4.Data);
        }
    }
    };
}
