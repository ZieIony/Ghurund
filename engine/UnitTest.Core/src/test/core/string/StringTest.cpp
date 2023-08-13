#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"

#include "core/collection/Tree.h"
#include "core/string/String.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
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

    TEST_METHOD(String_findChar) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::AreEqual(0ull, str.find(_T("tes"), 0));
            Assert::AreEqual(1ull, str.find(_T("est"), 0));
            Assert::AreEqual(3ull, str.find(_T("t"), 2));
            Assert::AreEqual(11ull, str.find(_T("float"), 0));
            AString astr = "test string";
            Assert::AreEqual(0ull, astr.find("tes", 0));
            Assert::AreEqual(1ull, astr.find("est", 0));
            Assert::AreEqual(3ull, astr.find("t", 2));
            Assert::AreEqual(11ull, astr.find("float", 0));
            WString wstr = L"test string";
            Assert::AreEqual(0ull, wstr.find(L"tes", 0));
            Assert::AreEqual(1ull, wstr.find(L"est", 0));
            Assert::AreEqual(3ull, wstr.find(L"t", 2));
            Assert::AreEqual(11ull, wstr.find(L"float", 0));
        }
    }

    TEST_METHOD(String_findString) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::AreEqual(0ull, str.find(String(_T("tes")), 0));
            Assert::AreEqual(1ull, str.find(String(_T("est")), 0));
            Assert::AreEqual(3ull, str.find(String(_T("t")), 2));
            Assert::AreEqual(11ull, str.find(String(_T("float")), 0));
            AString astr = "test string";
            Assert::AreEqual(0ull, astr.find(AString("tes"), 0));
            Assert::AreEqual(1ull, astr.find(AString("est"), 0));
            Assert::AreEqual(3ull, astr.find(AString("t"), 2));
            Assert::AreEqual(11ull, astr.find(AString("float"), 0));
            WString wstr = L"test string";
            Assert::AreEqual(0ull, wstr.find(WString(L"tes"), 0));
            Assert::AreEqual(1ull, wstr.find(WString(L"est"), 0));
            Assert::AreEqual(3ull, wstr.find(WString(L"t"), 2));
            Assert::AreEqual(11ull, wstr.find(WString(L"float"), 0));
        }
    }

    TEST_METHOD(String_findLastChar) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::AreEqual(0ull, str.findLast(_T("tes")));
            Assert::AreEqual(6ull, str.findLast(_T("t")));
            Assert::AreEqual(11ull, str.findLast(_T("float")));
            AString astr = "test string";
            Assert::AreEqual(0ull, astr.findLast("tes"));
            Assert::AreEqual(6ull, astr.findLast("t"));
            Assert::AreEqual(11ull, astr.findLast("float"));
            WString wstr = L"test string";
            Assert::AreEqual(0ull, wstr.findLast(L"tes"));
            Assert::AreEqual(6ull, wstr.findLast(L"t"));
            Assert::AreEqual(11ull, wstr.findLast(L"float"));
        }
    }

    TEST_METHOD(String_findLastString) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::AreEqual(0ull, str.findLast(String(_T("tes"))));
            Assert::AreEqual(6ull, str.findLast(String(_T("t"))));
            Assert::AreEqual(11ull, str.findLast(String(_T("float"))));
            AString astr = "test string";
            Assert::AreEqual(0ull, astr.findLast(AString("tes")));
            Assert::AreEqual(6ull, astr.findLast(AString("t")));
            Assert::AreEqual(11ull, astr.findLast(AString("float")));
            WString wstr = L"test string";
            Assert::AreEqual(0ull, wstr.findLast(WString(L"tes")));
            Assert::AreEqual(6ull, wstr.findLast(WString(L"t")));
            Assert::AreEqual(11ull, wstr.findLast(WString(L"float")));
        }
    }

    TEST_METHOD(String_startsWithChar) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::IsTrue(str.startsWith(_T("tes")));
            Assert::IsFalse(str.startsWith(_T("est")));
            AString astr = "test string";
            Assert::IsTrue(astr.startsWith("tes"));
            Assert::IsFalse(astr.endsWith("est"));
            WString wstr = L"test string";
            Assert::IsTrue(wstr.startsWith(L"tes"));
            Assert::IsFalse(wstr.endsWith(L"est"));
        }
    }

    TEST_METHOD(String_startsWithString) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::IsTrue(str.startsWith(String(_T("tes"))));
            Assert::IsFalse(str.startsWith(String(_T("est"))));
            AString astr = "test string";
            Assert::IsTrue(astr.startsWith(AString("tes")));
            Assert::IsFalse(astr.endsWith(AString("est")));
            WString wstr = L"test string";
            Assert::IsTrue(wstr.startsWith(WString(L"tes")));
            Assert::IsFalse(wstr.endsWith(WString(L"est")));
        }
    }

    TEST_METHOD(String_containsChar) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::IsTrue(str.contains(_T("est")));
            Assert::IsFalse(str.contains(_T("set")));
            AString astr = "test string";
            Assert::IsTrue(astr.contains("est"));
            Assert::IsFalse(astr.contains("set"));
            WString wstr = L"test string";
            Assert::IsTrue(wstr.contains(L"est"));
            Assert::IsFalse(wstr.contains(L"set"));
        }
    }

    TEST_METHOD(String_containsString) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::IsTrue(str.contains(String(_T("est"))));
            Assert::IsFalse(str.contains(String(_T("set"))));
            AString astr = "test string";
            Assert::IsTrue(astr.contains(AString("est")));
            Assert::IsFalse(astr.contains(AString("set")));
            WString wstr = L"test string";
            Assert::IsTrue(wstr.contains(WString(L"est")));
            Assert::IsFalse(wstr.contains(WString(L"set")));
        }
    }

    TEST_METHOD(String_endsWithChar) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::IsTrue(str.endsWith(_T("ing")));
            Assert::IsFalse(str.endsWith(_T("est")));
            AString astr = "test string";
            Assert::IsTrue(astr.endsWith("ing"));
            Assert::IsFalse(astr.endsWith("est"));
            WString wstr = L"test string";
            Assert::IsTrue(wstr.endsWith(L"ing"));
            Assert::IsFalse(wstr.endsWith(L"est"));
        }
    }

    TEST_METHOD(String_endsWithString) {
        MemoryGuard guard;
        {
            String str = _T("test string");
            Assert::IsTrue(str.endsWith(String(_T("ing"))));
            Assert::IsFalse(str.endsWith(String(_T("est"))));
            AString astr = "test string";
            Assert::IsTrue(astr.endsWith(AString("ing")));
            Assert::IsFalse(astr.endsWith(AString("est")));
            WString wstr = L"test string";
            Assert::IsTrue(wstr.endsWith(WString(L"ing")));
            Assert::IsFalse(wstr.endsWith(WString(L"est")));
        }
    }
    };
}
