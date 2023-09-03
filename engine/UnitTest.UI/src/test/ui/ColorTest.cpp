#include "pch.h"
#include "CppUnitTest.h"

#include "ui/Color.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ColorTest) {
private:
    bool cmpf(float A, float B, float epsilon = 0.005f) {
        return (fabs(A - B) < epsilon);
    }

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

    TEST_METHOD(Color_constructorInt) {
        Color color = 0x3f7fbf00;
        Assert::AreEqual(0.25f, color.A, 0.01f);
        Assert::AreEqual(0.5f, color.R, 0.01f);
        Assert::AreEqual(0.75f, color.G, 0.01f);
        Assert::AreEqual(0.0f, color.B, 0.01f);
        Assert::AreEqual(0x3f7fbf00ui32, color.Value);
    }

    TEST_METHOD(Color_constructorInts) {
        {
            Color color = Color(0x7fui8, 0xbf, 0x00);
            Assert::AreEqual(1.0f, color.A, 0.01f);
            Assert::AreEqual(0.5f, color.R, 0.01f);
            Assert::AreEqual(0.75f, color.G, 0.01f);
            Assert::AreEqual(0.0f, color.B, 0.01f);
            Assert::AreEqual(0xff7fbf00ui32, color.Value);
        }
        {
            Color color = Color(0x3fui8, 0x7f, 0xbf, 0x00);
            Assert::AreEqual(0.25f, color.A, 0.01f);
            Assert::AreEqual(0.5f, color.R, 0.01f);
            Assert::AreEqual(0.75f, color.G, 0.01f);
            Assert::AreEqual(0.0f, color.B, 0.01f);
            Assert::AreEqual(0x3f7fbf00ui32, color.Value);
        }
    }

    TEST_METHOD(Color_constructorFloats) {
        {
            Color color = Color(0.5f, 0.75f, 0.0f);
            Assert::AreEqual(1.0f, color.A);
            Assert::AreEqual(0.5f, color.R);
            Assert::AreEqual(0.75f, color.G);
            Assert::AreEqual(0.0f, color.B);
            Assert::AreEqual(0xff7fbf00ui32, color.Value);
        }
        {
            Color color = Color(0.25f, 0.5f, 0.75f, 0.0f);
            Assert::AreEqual(0.25f, color.A);
            Assert::AreEqual(0.5f, color.R);
            Assert::AreEqual(0.75f, color.G);
            Assert::AreEqual(0.0f, color.B);
            Assert::AreEqual(0x3f7fbf00ui32, color.Value);
        }
    }

    TEST_METHOD(Color_a) {
        Color color = 0xffffffff;
        color.A = 0.0f;
        Assert::AreEqual(0.0f, color.A, 0.01f);
        Assert::AreEqual(1.0f, color.R, 0.01f);
        Assert::AreEqual(1.0f, color.G, 0.01f);
        Assert::AreEqual(1.0f, color.B, 0.01f);
        Assert::AreEqual(0x00ffffffui32, color.Value);
    }

    TEST_METHOD(Color_r) {
        Color color = 0xffffffff;
        color.R = 0.0f;
        Assert::AreEqual(1.0f, color.A, 0.01f);
        Assert::AreEqual(0.0f, color.R, 0.01f);
        Assert::AreEqual(1.0f, color.G, 0.01f);
        Assert::AreEqual(1.0f, color.B, 0.01f);
        Assert::AreEqual(0xff00ffffui32, color.Value);
    }

    TEST_METHOD(Color_g) {
        Color color = 0xffffffff;
        color.G = 0.0f;
        Assert::AreEqual(1.0f, color.A, 0.01f);
        Assert::AreEqual(1.0f, color.R, 0.01f);
        Assert::AreEqual(0.0f, color.G, 0.01f);
        Assert::AreEqual(1.0f, color.B, 0.01f);
        Assert::AreEqual(0xffff00ffui32, color.Value);
    }

    TEST_METHOD(Color_b) {
        Color color = 0xffffffff;
        color.B = 0.0f;
        Assert::AreEqual(1.0f, color.A, 0.01f);
        Assert::AreEqual(1.0f, color.R, 0.01f);
        Assert::AreEqual(1.0f, color.G, 0.01f);
        Assert::AreEqual(0.0f, color.B, 0.01f);
        Assert::AreEqual(0xffffff00ui32, color.Value);
    }
    };
}
