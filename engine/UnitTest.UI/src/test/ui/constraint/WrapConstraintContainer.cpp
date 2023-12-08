#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include <test/TestLogOutput.h>

#include "ui/constraint/ConstraintFactory.h"
#include "test/ui/ShapeFactory.h"
#include "test/ui/ImageDrawableFactory.h"
#include "test/ui/TextFormatFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/SiblingConstraint.h"
#include "ui/constraint/ParentConstraint.h"
#include <ui/control/ControlContainer.h>
#include <ui/control/ColorView.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(WrapConstraintContainerTest) {
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

    TEST_METHOD(wrapEmpty) {
        MemoryGuard guard;
        {
            auto container = makeShared<ControlContainer>();
            container->Constraints = {
                .width = makeShared<WrapWidthConstraint>(),
                .height = makeShared<WrapHeightConstraint>()
            };

            ConstraintGraph graph;
            container->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(0.0f, container->Width.Value);
            Assert::AreEqual(0.0f, container->Height.Value);
        }
    }

    TEST_METHOD(wrapEmptyMinRatioOffset) {
        MemoryGuard guard;
        {
            auto container = makeShared<ControlContainer>();
            container->Constraints = {
                .width = []() {
                    auto c = makeShared<WrapWidthConstraint>();
                    c->Min = 100;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }(),
                .height = []() {
                    auto c = makeShared<WrapHeightConstraint>();
                    c->Min = 75;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }()
            };

            ConstraintGraph graph;
            container->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(100.0f, container->Width.Value);
            Assert::AreEqual(75.0f, container->Height.Value);
        }
    }

    TEST_METHOD(wrapChild) {
        MemoryGuard guard;
        {
            auto child = makeShared<ColorView>();
            child->Constraints = {
                .width = 100.0f,
                .height = 75.0f
            };
            auto group = makeShared<ControlContainer>();
            group->Child = child.get();
            group->Constraints = ConstraintSet{
                .width = makeShared<WrapWidthConstraint>(),
                .height = makeShared<WrapHeightConstraint>()
            };

            ConstraintGraph graph;
            group->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(100.0f, group->Width.Value);
            Assert::AreEqual(75.0f, group->Height.Value);
        }
    }

    TEST_METHOD(wrapChildFillMinRatioOffset) {
        MemoryGuard guard;
        {
            auto child = makeShared<ColorView>();
            child->Constraints = {
                .width = []() {
                    auto c = makeShared<ParentWidthConstraint>();
                    c->Min = 100.0f;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }(),
                .height = []() {
                    auto c = makeShared<ParentHeightConstraint>();
                    c->Min = 75.0f;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }()
            };

            auto group = makeShared<ControlContainer>();
            group->Child = child.get();
            group->Constraints = {
                .width = makeShared<WrapWidthConstraint>(),
                .height = makeShared<WrapHeightConstraint>()
            };

            ConstraintGraph graph;
            group->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(0.0f, group->Width.Value);
            Assert::AreEqual(0.0f, group->Height.Value);
        }
    }
    };
}