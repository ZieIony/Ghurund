#include "pch.h"
#include "CppUnitTest.h"
#include "test/ui/image/TestImage.h"
#include "test/TestUtils.h"
#include "test/ui/control/ControlTestTemplate.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    class TestControl:public Control {};

    TEST_CLASS(ControlTest) {
public:

    TEST_METHOD(measureWrap) {
        UnitTest::Utils::measureEmptyWrap<TestControl>();
    }

    TEST_METHOD(measureFill) {
        UnitTest::Utils::measureEmptyFill<TestControl>();
    }

    TEST_METHOD(measurePixels) {
        UnitTest::Utils::measureEmptyPixels<TestControl>();
    }

    TEST_METHOD(measurePercent) {
        UnitTest::Utils::measureEmptyPercent<TestControl>();
    }

    TEST_METHOD(measureRatioWidth) {
        UnitTest::Utils::measureEmptyRatioWidth<TestControl>();
    }

    TEST_METHOD(measureRatioHeight) {
        UnitTest::Utils::measureEmptyRatioHeight<TestControl>();
    }
    };
}
