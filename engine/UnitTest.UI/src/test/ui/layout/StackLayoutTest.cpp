#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/ui/control/ControlTestTemplate.h"

#include "ui/layout/StackLayout.h"
#include "ui/control/ColorView.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::UI;

    TEST_CLASS(StackLayoutTest) {
public:

    TEST_METHOD(measureContentWrapFill) {
        MemoryGuard guard;
        {
            SharedPointer<StackLayout> stackLayout = new StackLayout();
            stackLayout->PreferredSize = { Ghurund::UI::PreferredSize::Width::WRAP, Ghurund::UI::PreferredSize::Height::WRAP };

            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { Ghurund::UI::PreferredSize::Width::FILL, Ghurund::UI::PreferredSize::Height::FILL };
            stackLayout->Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };

            stackLayout->Children.add(testContent2);
            stackLayout->measure(100, 100);
            Assert::AreEqual({ 20,30 }, stackLayout->MeasuredSize);
        }
    }

    TEST_METHOD(measureContentWrapWrap) {
        MemoryGuard guard;
        {
            SharedPointer<StackLayout> stackLayout = new StackLayout();
            stackLayout->PreferredSize = { Ghurund::UI::PreferredSize::Width::WRAP, Ghurund::UI::PreferredSize::Height::WRAP };

            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { Ghurund::UI::PreferredSize::Width::WRAP, Ghurund::UI::PreferredSize::Height::WRAP };
            stackLayout->Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };

            stackLayout->Children.add(testContent2);
            stackLayout->measure(100, 100);
            Assert::AreEqual({ 20,30 }, stackLayout->MeasuredSize);
        }
    }

    TEST_METHOD(measureContentWrapRatio) {
        MemoryGuard guard;
        {
            SharedPointer<StackLayout> stackLayout = new StackLayout();
            stackLayout->PreferredSize = { Ghurund::UI::PreferredSize::Width::WRAP, Ghurund::UI::PreferredSize::Height::WRAP };
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { Ghurund::UI::PreferredSize::Width::FILL, Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::RATIO, 0.5f) };
            stackLayout->Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout->Children.add(testContent2);
            stackLayout->measure(100, 100);
            Assert::AreEqual({ 20,30 }, stackLayout->MeasuredSize);
        }
    }

    TEST_METHOD(measureContentWrapPercent) {
        MemoryGuard guard;
        {
            SharedPointer<StackLayout> stackLayout = new StackLayout();
            stackLayout->PreferredSize = { Ghurund::UI::PreferredSize::Width::WRAP, Ghurund::UI::PreferredSize::Height::WRAP };
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { Ghurund::UI::PreferredSize::Width::FILL, Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::PERCENT, 50) };
            stackLayout->Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout->Children.add(testContent2);
            stackLayout->measure(100, 100);
            Assert::AreEqual({ 20,30 }, stackLayout->MeasuredSize);
        }
    }

    TEST_METHOD(measureEmptyWrap) {
        UnitTest::Utils::measureEmptyWrap<StackLayout>();
    }

    TEST_METHOD(measureContentWrap) {
        UnitTest::Utils::measureContentWrap<StackLayout>([](StackLayout& stackLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent2);
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyFill) {
        UnitTest::Utils::measureEmptyFill<StackLayout>();
    }

    TEST_METHOD(measureContentFill) {
        UnitTest::Utils::measureContentFill<StackLayout>([](StackLayout& stackLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent2);
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyPixels) {
        UnitTest::Utils::measureEmptyPixels<StackLayout>();
    }

    TEST_METHOD(measureContentPixels) {
        UnitTest::Utils::measureContentPixels<StackLayout>([](StackLayout& stackLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent2);
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyPercent) {
        UnitTest::Utils::measureEmptyPercent<StackLayout>();
    }

    TEST_METHOD(measureContentPercent) {
        UnitTest::Utils::measureContentPercent<StackLayout>([](StackLayout& stackLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent2);
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyRatioWidth) {
        UnitTest::Utils::measureEmptyRatioWidth<StackLayout>();
    }

    TEST_METHOD(measureContentRatioWidth) {
        UnitTest::Utils::measureContentRatioWidth<StackLayout>([](StackLayout& stackLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent2);
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyRatioHeight) {
        UnitTest::Utils::measureEmptyRatioHeight<StackLayout>();
    }

    TEST_METHOD(measureContentRatioHeight) {
        UnitTest::Utils::measureContentRatioHeight<StackLayout>([](StackLayout& stackLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            stackLayout.Children.add(testContent2);
            return FloatSize{ 20, 30 };
        });
    }
    };
}
