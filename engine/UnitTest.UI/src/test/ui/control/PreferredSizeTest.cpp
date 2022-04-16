#include "pch.h"
#include "CppUnitTest.h"

#include "ui/PreferredSize.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(PreferredSizeTest) {
public:

    TEST_METHOD(parseWrap) {
        PreferredSize size = PreferredSize::parse("wrap, wrap");
        Assert::AreEqual(PreferredSize::Width::WRAP, size.width);
        Assert::AreEqual(PreferredSize::Height::WRAP, size.height);
    }

    TEST_METHOD(parseWrapSpaces) {
        PreferredSize size = PreferredSize::parse(" wrap , wrap ");
        Assert::AreEqual(PreferredSize::Width::WRAP, size.width);
        Assert::AreEqual(PreferredSize::Height::WRAP, size.height);
    }

    TEST_METHOD(parseFill) {
        PreferredSize size = PreferredSize::parse("fill, fill");
        Assert::AreEqual(PreferredSize::Width::FILL, size.width);
        Assert::AreEqual(PreferredSize::Height::FILL, size.height);
    }

    TEST_METHOD(parseValueZero) {
        PreferredSize size = PreferredSize::parse("0.0, 0.0");
        Assert::AreEqual(PreferredSize::Width(PreferredSize::Type::PIXELS, 0.0f), size.width);
        Assert::AreEqual(PreferredSize::Height(PreferredSize::Type::PIXELS, 0.0f), size.height);
    }

    TEST_METHOD(parseValue) {
        PreferredSize size = PreferredSize::parse("500.0, 12.5");
        Assert::AreEqual(PreferredSize::Width(PreferredSize::Type::PIXELS, 500.0f), size.width);
        Assert::AreEqual(PreferredSize::Height(PreferredSize::Type::PIXELS, 12.5f), size.height);
    }

    TEST_METHOD(parseValueComma) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("5,0, wrap");
        });
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("wrap, 5,0");
        });
    }

    TEST_METHOD(parseValueF) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("5.0f, wrap");
        });
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("wrap, 5.0f");
        });
    }

    TEST_METHOD(parseText) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("wrap, five");
        });
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("five, wrap");
        });
    }

    TEST_METHOD(parsePercentZero) {
        PreferredSize size = PreferredSize::parse("0.0%, 0.0%");
        Assert::AreEqual(PreferredSize::Width(PreferredSize::Type::PERCENT, 0.0f), size.width);
        Assert::AreEqual(PreferredSize::Height(PreferredSize::Type::PERCENT, 0.0f), size.height);
    }

    TEST_METHOD(parsePercent) {
        PreferredSize size = PreferredSize::parse("500.0%, 12.5%");
        Assert::AreEqual(PreferredSize::Width(PreferredSize::Type::PERCENT, 500.0f), size.width);
        Assert::AreEqual(PreferredSize::Height(PreferredSize::Type::PERCENT, 12.5f), size.height);
    }

    TEST_METHOD(parsePercentComma) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("5,0%, wrap");
        });
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("wrap, 5,0%");
        });
    }

    TEST_METHOD(parsePercentSpace) {
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("5.0 %, wrap");
        });
        Assert::ExpectException<std::invalid_argument, void>([] {
            PreferredSize size = PreferredSize::parse("wrap, 5.0 %");
        });
    }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    static std::wstring ToString<Ghurund::UI::PreferredSize::Width>(const Ghurund::UI::PreferredSize::Width& t) {
        if (t.Type == Ghurund::UI::PreferredSize::Type::PIXELS) {
            return std::format(L"{}", t.Value);
        } else if (t.Type == Ghurund::UI::PreferredSize::Type::PERCENT) {
            return std::format(L"{}%", t.Value);
        } else if (t.Type == Ghurund::UI::PreferredSize::Type::WRAP) {
            return L"wrap";
        } else {
            return L"fill";
        }
    }

    template<>
    static std::wstring ToString<Ghurund::UI::PreferredSize::Height>(const Ghurund::UI::PreferredSize::Height& t) {
        if (t.Type == Ghurund::UI::PreferredSize::Type::PIXELS) {
            return std::format(L"{}", t.Value);
        } else if (t.Type == Ghurund::UI::PreferredSize::Type::PERCENT) {
            return std::format(L"{}%", t.Value);
        } else if (t.Type == Ghurund::UI::PreferredSize::Type::WRAP) {
            return L"wrap";
        } else {
            return L"fill";
        }
    }
}
