#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"

#include "ui/control/ColorView.h"
#include "ui/control/ControlGroup.h"
#include "ui/control/ControlPath.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    static std::wstring ToString<Ghurund::UI::ColorView>(const Ghurund::UI::ColorView& t) {
        return std::format(L"{}", t.toString());
    }

    template<>
    static std::wstring ToString<Ghurund::UI::Constraint>(const Ghurund::UI::Constraint& t) {
        return std::format(L"{}", t.toString());
    }
}

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ControlCloningTest) {
public:

    TEST_METHOD(ColorView_clone) {
        auto original = makeShared<ColorView>();
        original->Color = ColorValue(0xffff0000);
        SharedPointer<ColorView> clone((ColorView*)original->clone());
        Assert::AreNotSame(*original.get(), *clone.get());
        Assert::AreEqual(*original.get(), *clone.get());
    }
    };
}
