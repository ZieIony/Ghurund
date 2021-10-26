#include "pch.h"
#include "CppUnitTest.h"

#include "ui/Alignment.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(AlignmentTest) {
public:

    TEST_METHOD(Alignment_parseLeftTop) {
        Alignment alignment = Alignment::parse("left, top");
        Assert::AreEqual(Alignment::Horizontal::LEFT, alignment.horizontal);
        Assert::AreEqual(Alignment::Vertical::TOP, alignment.vertical);
    }

    TEST_METHOD(Alignment_parseCenterCenter) {
        Alignment alignment = Alignment::parse("center, center");
        Assert::AreEqual(Alignment::Horizontal::CENTER, alignment.horizontal);
        Assert::AreEqual(Alignment::Vertical::CENTER, alignment.vertical);
    }

    TEST_METHOD(Alignment_parseRightBottom) {
        Alignment alignment = Alignment::parse("right, bottom");
        Assert::AreEqual(Alignment::Horizontal::RIGHT, alignment.horizontal);
        Assert::AreEqual(Alignment::Vertical::BOTTOM, alignment.vertical);
    }

    TEST_METHOD(Alignment_parseSpaces) {
        Alignment alignment = Alignment::parse("  right  , bottom ");
        Assert::AreEqual(Alignment::Horizontal::RIGHT, alignment.horizontal);
        Assert::AreEqual(Alignment::Vertical::BOTTOM, alignment.vertical);
    }

    TEST_METHOD(Alignment_parseText) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            Alignment alignment = Alignment::parse("invalid alignment");
        });
    }

    TEST_METHOD(Alignment_parseOneValue) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            Alignment alignment = Alignment::parse("center");
        });
    }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    static std::wstring ToString<Ghurund::UI::Alignment::Horizontal>(const Ghurund::UI::Alignment::Horizontal& t) {
        if (t == Ghurund::UI::Alignment::Horizontal::LEFT) {
            return L"left";
        } else if (t == Ghurund::UI::Alignment::Horizontal::CENTER) {
            return L"center";
        } else {
            return L"right";
        }
    }

    template<>
    static std::wstring ToString<Ghurund::UI::Alignment::Vertical>(const Ghurund::UI::Alignment::Vertical& t) {
        if (t == Ghurund::UI::Alignment::Vertical::TOP) {
            return L"top";
        } else if (t == Ghurund::UI::Alignment::Vertical::CENTER) {
            return L"center";
        } else {
            return L"bottom";
        }
    }
}
