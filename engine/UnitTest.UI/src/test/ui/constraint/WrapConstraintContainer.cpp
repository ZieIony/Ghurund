#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"

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

    TEST_METHOD(wrapEmpty) {
        MemoryGuard guard;
        {
            SharedPointer<ControlContainer> container = ghnew ControlContainer();
            container->setConstraints({
                .width = std::make_shared<WrapWidthConstraint>(),
                .height = std::make_shared<WrapHeightConstraint>()
                });

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
            SharedPointer<ControlContainer> container = ghnew ControlContainer();
            container->setConstraints({
                .width = []() {
                    auto c = std::make_shared<WrapWidthConstraint>();
                    c->Min = 100;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }(),
                .height = []() {
                    auto c = std::make_shared<WrapHeightConstraint>();
                    c->Min = 75;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }()
                });

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
            SharedPointer<ColorView> child = ghnew ColorView();
            child->setConstraints({
                .width = std::make_shared<ValueConstraint>(100.0f),
                .height = std::make_shared<ValueConstraint>(75.0f)
                });

            SharedPointer<ControlContainer> group = ghnew ControlContainer();
            group->Child = child;
            group->setConstraints({
                .width = std::make_shared<WrapWidthConstraint>(),
                .height = std::make_shared<WrapHeightConstraint>()
                });

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
            SharedPointer<ColorView> child = ghnew ColorView();
            child->setConstraints({
                .width = []() {
                    auto c = std::make_shared<ParentWidthConstraint>();
                    c->Min = 100.0f;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }(),
                .height = []() {
                    auto c = std::make_shared<ParentHeightConstraint>();
                    c->Min = 75.0f;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }()
                });

            SharedPointer<ControlContainer> group = ghnew ControlContainer();
            group->Child = child;
            group->setConstraints({
                .width = std::make_shared<WrapWidthConstraint>(),
                .height = std::make_shared<WrapHeightConstraint>()
                });

            ConstraintGraph graph;
            group->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(100.0f, group->Width.Value);
            Assert::AreEqual(75.0f, group->Height.Value);
        }
    }
    };
}