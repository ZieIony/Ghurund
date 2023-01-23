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

    TEST_CLASS(VerticalLayoutTest) {
public:

    TEST_METHOD(measureEmptyWrap) {
        UnitTest::Utils::measureEmptyWrap<VerticalLayout>();
    }

    TEST_METHOD(measureContentWrap) {
        UnitTest::Utils::measureContentWrap<VerticalLayout>([](VerticalLayout& verticalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            //testContent->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            //testContent2->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }

    TEST_METHOD(measureEmptyFill) {
        UnitTest::Utils::measureEmptyFill<VerticalLayout>();
    }

    TEST_METHOD(measureContentFill) {
        UnitTest::Utils::measureContentFill<VerticalLayout>([](VerticalLayout& verticalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            //testContent->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            //testContent2->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }

    TEST_METHOD(measureEmptyPixels) {
        UnitTest::Utils::measureEmptyPixels<VerticalLayout>();
    }

    TEST_METHOD(measureContentPixels) {
        UnitTest::Utils::measureContentPixels<VerticalLayout>([](VerticalLayout& verticalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            //testContent->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            //testContent2->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }

    TEST_METHOD(measureEmptyPercent) {
        UnitTest::Utils::measureEmptyPercent<VerticalLayout>();
    }

    TEST_METHOD(measureContentPercent) {
        UnitTest::Utils::measureContentPercent<VerticalLayout>([](VerticalLayout& verticalLayout) {
            SharedPointer<ColorView> testContent = new ColorView();
            //testContent->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent);
            SharedPointer<ColorView> testContent2 = new ColorView();
            //testContent2->PreferredSize = { 20, 30 };
            verticalLayout.Children.add(testContent2);
            return FloatSize{ 20, 60 };
        });
    }
    };
}
