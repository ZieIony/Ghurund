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
#include "ui/control/ControlGroup.h"
#include <ui/control/ColorView.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(WrapConstraintGroupTest) {
public:

    TEST_METHOD(wrapEmpty) {
        MemoryGuard guard;
        {
            SharedPointer<ControlGroup> group = ghnew ControlGroup();
            group->setConstraints({
                .width = std::make_shared<WrapWidthConstraint>(),
                .height = std::make_shared<WrapHeightConstraint>()
                });

            ConstraintGraph graph;
            group->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(0.0f, group->Width.Value);
            Assert::AreEqual(0.0f, group->Height.Value);
        }
    }

    TEST_METHOD(wrapEmptyMinRatioOffset) {
        MemoryGuard guard;
        {
            SharedPointer<ControlGroup> group = ghnew ControlGroup();
            group->setConstraints({
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
            group->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(100.0f, group->Width.Value);
            Assert::AreEqual(75.0f, group->Height.Value);
        }
    }

    TEST_METHOD(wrapChildren) {
        MemoryGuard guard;
        {
            SharedPointer<ColorView> child1 = ghnew ColorView();
            child1->setConstraints({
                .width = std::make_shared<ValueConstraint>(100.0f),
                .height = std::make_shared<ValueConstraint>(75.0f)
                });

            SharedPointer<ColorView> child2 = ghnew ColorView();
            child2->setConstraints({
                .width = std::make_shared<ValueConstraint>(150.0f),
                .height = std::make_shared<ValueConstraint>(50.0f)
                });

            SharedPointer<ControlGroup> group = ghnew ControlGroup();
            group->Children.addAll({ child1, child2 });
            group->setConstraints({
                .width = std::make_shared<WrapWidthConstraint>(),
                .height = std::make_shared<WrapHeightConstraint>()
                });

            ConstraintGraph graph;
            group->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(150.0f, group->Width.Value);
            Assert::AreEqual(75.0f, group->Height.Value);
        }
    }

    TEST_METHOD(wrapChildrenValueFill) {
        MemoryGuard guard;
        {
            SharedPointer<ColorView> child1 = ghnew ColorView();
            child1->setConstraints({
                .width = std::make_shared<ValueConstraint>(100.0f),
                .height = std::make_shared<ValueConstraint>(75.0f)
                });
            SharedPointer<ColorView> child2 = ghnew ColorView();
            child2->setConstraints({
                .width = std::make_shared<ParentWidthConstraint>(),
                .height = std::make_shared<ParentHeightConstraint>()
                });

            SharedPointer<ControlGroup> group = ghnew ControlGroup();
            group->Children.addAll({ child1, child2 });
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
            Assert::AreEqual(100.0f, child2->Width.Value);
            Assert::AreEqual(75.0f, child2->Height.Value);
        }
    }

    TEST_METHOD(wrapChildrenFillMinRatioOffset) {
        MemoryGuard guard;
        {
            SharedPointer<ColorView> child1 = ghnew ColorView();
            child1->setConstraints({
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
            SharedPointer<ColorView> child2 = ghnew ColorView();
            child2->setConstraints({
                .width = []() {
                    auto c = std::make_shared<WrapWidthConstraint>();
                    c->Min = 150;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }(),
                .height = []() {
                    auto c = std::make_shared<WrapHeightConstraint>();
                    c->Min = 50;
                    c->Ratio = 0.5f;
                    c->Offset = 10.0f;
                    return c;
                }()
                });

            SharedPointer<ControlGroup> group = ghnew ControlGroup();
            group->Children.addAll({ child1, child2 });
            group->setConstraints({
                .width = std::make_shared<WrapWidthConstraint>(),
                .height = std::make_shared<WrapHeightConstraint>()
                });

            ConstraintGraph graph;
            group->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(150.0f, group->Width.Value);
            Assert::AreEqual(75.0f, group->Height.Value);
        }
    }
    };
}