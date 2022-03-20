#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/ui/control/ControlTestTemplate.h"

#include "ui/layout/LinearLayout.h"
#include "ui/control/ColorView.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(HorizontalLayoutTest) {
public:

    TEST_METHOD(measureEmptyWrap) {
        UnitTest::Utils::measureEmptyWrap<HorizontalLayout>();
    }

    TEST_METHOD(measureContentWrap) {
        UnitTest::Utils::measureContentWrap<HorizontalLayout>([](HorizontalLayout& horizontalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }

    TEST_METHOD(measureEmptyFill) {
        UnitTest::Utils::measureEmptyFill<HorizontalLayout>();
    }

    TEST_METHOD(measureContentFill) {
        UnitTest::Utils::measureContentFill<HorizontalLayout>([](HorizontalLayout& horizontalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }

    TEST_METHOD(measureEmptyPixels) {
        UnitTest::Utils::measureEmptyPixels<HorizontalLayout>();
    }

    TEST_METHOD(measureContentPixels) {
        UnitTest::Utils::measureContentPixels<HorizontalLayout>([](HorizontalLayout& horizontalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }

    TEST_METHOD(measureEmptyPercent) {
        UnitTest::Utils::measureEmptyPercent<HorizontalLayout>();
    }

    TEST_METHOD(measureContentPercent) {
        UnitTest::Utils::measureContentPercent<HorizontalLayout>([](HorizontalLayout& horizontalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            testContent->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            testContent2->PreferredSize = { 20, 30 };
            horizontalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }
    };
}
