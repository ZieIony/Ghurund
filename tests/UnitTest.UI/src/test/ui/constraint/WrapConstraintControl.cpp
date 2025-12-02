#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/ui/UITestUtils.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestLogOutput.h"

#include <ui/control/ControlGroup.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(WrapConstraintControlTest) {
public:
    TEST_CLASS_INITIALIZE(classInitialize) {
        RefCountedObject::reservePointers(500);
        Ghurund::Core::Logger::init(std::make_unique<TestLogOutput>());
        TestLogOutput::initReportHook();
    }

    TEST_METHOD_CLEANUP(methodCleanup) {
        if (RefCountedObject::numberOfAllocatedPointers() > 0) {
            RefCountedObject::dumpPointers();
            Assert::Fail();
        }
    }

    TEST_METHOD(wrapEmpty) {
        MemoryGuard guard;
        {
            auto container = makeIntrusive<ControlGroup>();
            auto control = makeIntrusive<Control>();

            container->Children.add(control.get(), makeConstraints({
                .width = makeIntrusive<WrapWidthConstraint>(),
                .height = makeIntrusive<WrapHeightConstraint>()
            }));

            layoutControl(container, 100.0f, 100.0f);

            Assert::AreEqual(0.0f, control->Size.Width);
            Assert::AreEqual(0.0f, control->Size.Height);
        }
    }

    TEST_METHOD(wrapEmptyMinRatioOffset) {
        MemoryGuard guard;
        {
            auto container = makeIntrusive<ControlGroup>();
            auto control = makeIntrusive<Control>();
            container->Children.add(control.get(), makeConstraints({
                .width = [] {
                    auto c = makeIntrusive<WrapWidthConstraint>();
                    c->Min = 100;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }(),
                .height = [] {
                    auto c = makeIntrusive<WrapHeightConstraint>();
                    c->Min = 75;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }()
            }));

            layoutControl(container, 100, 100);

            Assert::AreEqual(100.0f, control->Size.Width);
            Assert::AreEqual(75.0f, control->Size.Height);
        }
    }
    };
}