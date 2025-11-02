#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/utils/TestUtils.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestLogOutput.h"

#include "ui/widget/button/Button.h"

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    TEST_CLASS(WidgetTest) {
public:
    TEST_CLASS_INITIALIZE(classInitialize) {
        TestUtils::testClassInitialize();
    }

    TEST_METHOD_CLEANUP(methodCleanup) {
        TestUtils::testMethodCleanup();
    }

    TEST_METHOD(emptyWidget) {
        MemoryGuard guard;
        {
            auto button = makeIntrusive<Button>();

            Assert::IsNull(button->Theme);
            //Assert::IsNull(button->Layout);
            //Assert::IsNull(button->Content);
        }
    }
    };
}