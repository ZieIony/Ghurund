#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/utils/TestUtils.h"

#include "ui/control/ColorView.h"
#include "ui/control/ControlGroup.h"
#include "ui/control/ControlPath.h"

#include <format>
#include <ui/constraint/ConstraintLayout.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    static std::wstring ToString<Ghurund::UI::Control>(const Ghurund::UI::Control& t) {
        return std::format(L"{}", t.toString());
    }
}

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ControlPathTest) {
public:

    TEST_METHOD(resolveParentGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout.get(), *result);
    }

    TEST_METHOD(resolveParentContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout.get(), *result);
    }

    TEST_METHOD(resolveEmptyParent) {
        auto content = makeIntrusive<ColorView>();
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNameGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveNameContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveMissingNameGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveMissingNameContainer) {
        auto layout = makeIntrusive<ConstraintLayout>();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        auto content2 = makeIntrusive<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content2.get(), *result);
    }

    TEST_METHOD(resolveNegativeIndexGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        auto content2 = makeIntrusive<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[-1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content2.get(), *result);
    }

    TEST_METHOD(resolveIndexMissingGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        auto content2 = makeIntrusive<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[2]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNegativeIndexMissingGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        auto content2 = makeIntrusive<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[-3]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    // [0] is the only valid index for containers
    TEST_METHOD(resolveNegativeIndexContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[-1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexMissingContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNegativeIndexMissingContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[-2]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveParentNameGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("Parent.'color'");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveParentNameContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("Parent.'color'");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveParentIndexGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto content = makeIntrusive<ColorView>();
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("Parent[0]");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveParentIndexContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto content = makeIntrusive<ColorView>();
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("Parent[0]");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveNameIndexGroup) {
        auto layout = makeIntrusive<ConstraintLayout>();
        auto mid = makeIntrusive<ConstraintLayout>();
        mid->Name = "container";
        layout->Children = { mid.get() };
        auto content = makeIntrusive<ColorView>();
        mid->Children = { content.get() };
        ControlPath path = ControlPath::parse("'container'[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveNameIndexContainer) {
        auto layout = makeIntrusive<ControlContainer>();
        auto mid = makeIntrusive<ControlContainer>();
        mid->Name = "container";
        layout->Child = mid.get();
        auto content = makeIntrusive<ColorView>();
        mid->Child = content.get();
        ControlPath path = ControlPath::parse("'container'[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveComplex1) {
        auto layout = makeIntrusive<ControlContainer>();
        auto container = makeIntrusive<ControlContainer>();
        container->Name = "container";
        layout->Child = container.get();
        ControlPath path = ControlPath::parse("'container'.Parent[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*container.get(), *result);
    }

    TEST_METHOD(resolveComplex2) {
        auto layout = makeIntrusive<ControlContainer>();
        auto mid = makeIntrusive<ControlContainer>();
        mid->Name = "container";
        layout->Child = mid.get();
        auto content = makeIntrusive<ColorView>();
        content->Name = "color";
        mid->Child = content.get();
        ControlPath path = ControlPath::parse("'container'.'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveComplex3) {
        auto layout = makeIntrusive<ControlContainer>();
        auto mid = makeIntrusive<ControlContainer>();
        layout->Child = mid.get();
        auto content = makeIntrusive<ColorView>();
        mid->Child = content.get();
        ControlPath path = ControlPath::parse("Parent.Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout.get(), *result);
    }

    TEST_METHOD(resolveInvalidPathNoQuotationMarks) {
        Assert::ExpectException<InvalidDataException>([] {
            ControlPath::parse("Parent.color");
        });
    }

    TEST_METHOD(resolveInvalidPathIndexAfterDot) {
        Assert::ExpectException<InvalidDataException>([] {
            ControlPath::parse("Parent.[5]");
        });
    }

    TEST_METHOD(resolveInvalidPathFloatIndex) {
        Assert::ExpectException<InvalidDataException>([] {
            ControlPath::parse("Parent[3.4]");
        });
    }

    TEST_METHOD(resolveInvalidPathTextIndex) {
        Assert::ExpectException<InvalidDataException>([] {
            ControlPath::parse("Parent[five]");
        });
    }

    TEST_METHOD(resolveInvalidPathParentLowerCase) {
        Assert::ExpectException<InvalidDataException>([] {
            ControlPath::parse("parent");
        });
    }

    };
}
