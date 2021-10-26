#include "pch.h"
#include "CppUnitTest.h"

#include "ui/Color.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ColorTest) {
public:

    TEST_METHOD(Color_parse) {
        Color color = Color::parse("#ffff00");
        Assert::AreEqual(0xffff00u, color.Value);
    }

    TEST_METHOD(Color_parseAlpha) {
        Color color = Color::parse("#f0abcd00");
        Assert::AreEqual(0xf0abcd00u, color.Value);
    }

    TEST_METHOD(Color_parseSpaces) {
        Color color = Color::parse("  #f0abcd00   ");
        Assert::AreEqual(0xf0abcd00u, color.Value);
    }

    TEST_METHOD(Color_parseNoSymbol) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            Color color = Color::parse("ffff00");
        });
    }

    TEST_METHOD(Color_parseText) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            Color color = Color::parse("red");
        });
    }

    TEST_METHOD(Color_parseExtraSpaces) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            Color color = Color::parse("#ff ff 00 00");
        });
    }
    };
}
