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
    static std::wstring ToString<Ghurund::UI::Control>(const Ghurund::UI::Control& t) {
        return std::format(L"{}", t.toString());
    }
}

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ControlPathTest) {
public:

    TEST_METHOD(resolveParentGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout.get(), *result);
    }

    TEST_METHOD(resolveParentContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout.get(), *result);
    }

    TEST_METHOD(resolveEmptyParent) {
        auto content = makeShared<ColorView>();
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNameGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveNameContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveMissingNameGroup) {
        auto layout = makeShared<ControlGroup>();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveMissingNameContainer) {
        auto layout = makeShared<ControlGroup>();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        auto content2 = makeShared<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content2.get(), *result);
    }

    TEST_METHOD(resolveNegativeIndexGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        auto content2 = makeShared<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[-1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content2.get(), *result);
    }

    TEST_METHOD(resolveIndexMissingGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        auto content2 = makeShared<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[2]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNegativeIndexMissingGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        auto content2 = makeShared<ColorView>();
        layout->Children = { content.get(), content2.get() };
        ControlPath path = ControlPath::parse("[-3]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    // [0] is the only valid index for containers
    TEST_METHOD(resolveNegativeIndexContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[-1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexMissingContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[1]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNegativeIndexMissingContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("[-2]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveParentNameGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("Parent.'color'");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveParentNameContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("Parent.'color'");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveParentIndexGroup) {
        auto layout = makeShared<ControlGroup>();
        auto content = makeShared<ColorView>();
        layout->Children.add(content.get());
        ControlPath path = ControlPath::parse("Parent[0]");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveParentIndexContainer) {
        auto layout = makeShared<ControlContainer>();
        auto content = makeShared<ColorView>();
        layout->Child = content.get();
        ControlPath path = ControlPath::parse("Parent[0]");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveNameIndexGroup) {
        auto layout = makeShared<ControlGroup>();
        auto mid = makeShared<ControlGroup>();
        mid->Name = "container";
        layout->Children = { mid.get() };
        auto content = makeShared<ColorView>();
        mid->Children = { content.get() };
        ControlPath path = ControlPath::parse("'container'[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveNameIndexContainer) {
        auto layout = makeShared<ControlContainer>();
        auto mid = makeShared<ControlContainer>();
        mid->Name = "container";
        layout->Child = mid.get();
        auto content = makeShared<ColorView>();
        mid->Child = content.get();
        ControlPath path = ControlPath::parse("'container'[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveComplex1) {
        auto layout = makeShared<ControlContainer>();
        auto container = makeShared<ControlContainer>();
        container->Name = "container";
        layout->Child = container.get();
        ControlPath path = ControlPath::parse("'container'.Parent[0]");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*container.get(), *result);
    }

    TEST_METHOD(resolveComplex2) {
        auto layout = makeShared<ControlContainer>();
        auto mid = makeShared<ControlContainer>();
        mid->Name = "container";
        layout->Child = mid.get();
        auto content = makeShared<ColorView>();
        content->Name = "color";
        mid->Child = content.get();
        ControlPath path = ControlPath::parse("'container'.'color'");
        Control* result = path.resolve(*layout.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content.get(), *result);
    }

    TEST_METHOD(resolveComplex3) {
        auto layout = makeShared<ControlContainer>();
        auto mid = makeShared<ControlContainer>();
        layout->Child = mid.get();
        auto content = makeShared<ColorView>();
        mid->Child = content.get();
        ControlPath path = ControlPath::parse("Parent.Parent");
        Control* result = path.resolve(*content.get());
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout.get(), *result);
    }

    TEST_METHOD(resolveInvalidPathNoQuotationMarks) {
        Assert::ExpectException<InvalidDataException>([]() {
            ControlPath::parse("Parent.color");
        });
    }

    TEST_METHOD(resolveInvalidPathIndexAfterDot) {
        Assert::ExpectException<InvalidDataException>([]() {
            ControlPath::parse("Parent.[5]");
        });
    }

    TEST_METHOD(resolveInvalidPathFloatIndex) {
        Assert::ExpectException<InvalidDataException>([]() {
            ControlPath::parse("Parent[3.4]");
        });
    }

    TEST_METHOD(resolveInvalidPathTextIndex) {
        Assert::ExpectException<InvalidDataException>([]() {
            ControlPath::parse("Parent[five]");
        });
    }

    TEST_METHOD(resolveInvalidPathParentLowerCase) {
        Assert::ExpectException<InvalidDataException>([]() {
            ControlPath::parse("parent");
        });
    }

    };
}
