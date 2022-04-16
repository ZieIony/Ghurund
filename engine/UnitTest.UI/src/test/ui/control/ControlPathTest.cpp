#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"

#include "ui/layout/StackLayout.h"
#include "ui/control/ColorView.h"
#include "ui/control/ControlPath.h"
#include "ui/control/PaddingContainer.h"

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
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        layout->Children.add(content);
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout, *result);
    }

    TEST_METHOD(resolveParentContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        layout->Child = content;
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout, *result);
    }

    TEST_METHOD(resolveEmptyParent) {
        SharedPointer<ColorView> content = new ColorView();
        ControlPath path = ControlPath::parse("Parent");
        Control* result = path.resolve(*content);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNameGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Children.add(content);
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveNameContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Child = content;
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveMissingNameGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveMissingNameContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        ControlPath path = ControlPath::parse("'color'");
        Control* result = path.resolve(*layout);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        SharedPointer<ColorView> content2 = new ColorView();
        layout->Children = { content, content2 };
        ControlPath path = ControlPath::parse("[1]");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content2, *result);
    }

    TEST_METHOD(resolveNegativeIndexGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        SharedPointer<ColorView> content2 = new ColorView();
        layout->Children = { content, content2 };
        ControlPath path = ControlPath::parse("[-1]");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content2, *result);
    }

    TEST_METHOD(resolveIndexMissingGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        SharedPointer<ColorView> content2 = new ColorView();
        layout->Children = { content, content2 };
        ControlPath path = ControlPath::parse("[2]");
        Control* result = path.resolve(*layout);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNegativeIndexMissingGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        SharedPointer<ColorView> content2 = new ColorView();
        layout->Children = { content, content2 };
        ControlPath path = ControlPath::parse("[-3]");
        Control* result = path.resolve(*layout);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Child = content;
        ControlPath path = ControlPath::parse("[0]");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    // [0] is the only valid index for containers
    TEST_METHOD(resolveNegativeIndexContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Child = content;
        ControlPath path = ControlPath::parse("[-1]");
        Control* result = path.resolve(*layout);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveIndexMissingContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Child = content;
        ControlPath path = ControlPath::parse("[1]");
        Control* result = path.resolve(*layout);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveNegativeIndexMissingContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Child = content;
        ControlPath path = ControlPath::parse("[-2]");
        Control* result = path.resolve(*layout);
        Assert::IsNull(result);
    }

    TEST_METHOD(resolveParentNameGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Children.add(content);
        ControlPath path = ControlPath::parse("Parent.'color'");
        Control* result = path.resolve(*content);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveParentNameContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        layout->Child = content;
        ControlPath path = ControlPath::parse("Parent.'color'");
        Control* result = path.resolve(*content);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveParentIndexGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<ColorView> content = new ColorView();
        layout->Children.add(content);
        ControlPath path = ControlPath::parse("Parent[0]");
        Control* result = path.resolve(*content);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveParentIndexContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<ColorView> content = new ColorView();
        layout->Child = content;
        ControlPath path = ControlPath::parse("Parent[0]");
        Control* result = path.resolve(*content);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveNameIndexGroup) {
        SharedPointer<StackLayout> layout = new StackLayout();
        SharedPointer<StackLayout> mid = new StackLayout();
        mid->Name = "container";
        layout->Children = { mid };
        SharedPointer<ColorView> content = new ColorView();
        mid->Children = { content };
        ControlPath path = ControlPath::parse("'container'[0]");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveNameIndexContainer) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<PaddingContainer> mid = new PaddingContainer();
        mid->Name = "container";
        layout->Child = mid;
        SharedPointer<ColorView> content = new ColorView();
        mid->Child = content;
        ControlPath path = ControlPath::parse("'container'[0]");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveComplex1) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<PaddingContainer> container = new PaddingContainer();
        container->Name = "container";
        layout->Child = container;
        ControlPath path = ControlPath::parse("'container'.Parent[0]");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*container, *result);
    }

    TEST_METHOD(resolveComplex2) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<PaddingContainer> mid = new PaddingContainer();
        mid->Name = "container";
        layout->Child = mid;
        SharedPointer<ColorView> content = new ColorView();
        content->Name = "color";
        mid->Child = content;
        ControlPath path = ControlPath::parse("'container'.'color'");
        Control* result = path.resolve(*layout);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*content, *result);
    }

    TEST_METHOD(resolveComplex3) {
        SharedPointer<PaddingContainer> layout = new PaddingContainer();
        SharedPointer<PaddingContainer> mid = new PaddingContainer();
        layout->Child = mid;
        SharedPointer<ColorView> content = new ColorView();
        mid->Child = content;
        ControlPath path = ControlPath::parse("Parent.Parent");
        Control* result = path.resolve(*content);
        Assert::IsNotNull(result);
        Assert::AreSame<Control>(*layout, *result);
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
