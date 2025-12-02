#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/utils/TestUtils.h"

#include "ui/control/ControlGroup.h"
#include "ui/control/ControlPath.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    static std::wstring ToString<Ghurund::UI::Control>(const Ghurund::UI::Control& t) {
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
        auto original = makeIntrusive<Control>();
        IntrusivePointer<Control> clone((Control*)original->clone());
        Assert::AreNotSame(*original.get(), *clone.get());
        Assert::AreEqual(*original.get(), *clone.get());
    }
    };
}
