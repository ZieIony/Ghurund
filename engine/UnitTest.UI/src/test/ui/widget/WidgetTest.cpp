#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include <test/TestLogOutput.h>

#include "ui/widget/button/Button.h"

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(WidgetTest) {
public:
    TEST_CLASS_INITIALIZE(classInitialize) {
        Pointer::reservePointers(500);
        Ghurund::Core::Logger::init(std::make_unique<TestLogOutput>());
        TestLogOutput::initReportHook();
    }

    TEST_METHOD_CLEANUP(methodCleanup) {
        if (Pointer::numberOfAllocatedPointers() > 0) {
            Pointer::dumpPointers();
            Assert::Fail();
        }
    }

    TEST_METHOD(emptyWidget) {
        MemoryGuard guard;
        {
            auto button = makeShared<Button>();

            Assert::IsNull(button->Theme);
            //Assert::IsNull(button->Layout);
            //Assert::IsNull(button->Content);
        }
    }
    };
}