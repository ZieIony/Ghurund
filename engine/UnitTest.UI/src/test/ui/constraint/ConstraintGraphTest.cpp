#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include "test/TestLogOutput.h"

#include "ui/constraint/Constraint.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/constraint/WrapConstraint.h"

#include <format>
#include <ui/control/ColorView.h>

using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Ghurund::Core;
using namespace Ghurund::UI;

namespace UnitTest {
    TEST_CLASS(ConstraintGraphTest) {
public:
    TEST_CLASS_INITIALIZE(classInitialize) {
        Ghurund::Core::Logger::init(std::make_unique<TestLogOutput>());
        TestLogOutput::initReportHook();
        Pointer::reservePointers(100);
    }

    TEST_METHOD_CLEANUP(methodCleanup) {
        Pointer::dumpPointers();
    }

    TEST_METHOD(simple) {
        MemoryGuard guard;
        {
            SharedPointer<ValueConstraint> c0 = ghnew ValueConstraint(0.0f), c1 = ghnew ValueConstraint(0.0f);
            c0->Dependencies.add(&c1);
            ConstraintGraph graph;
            graph.addAll({ &c0, &c1 });
            graph.sort();
            Assert::IsTrue(&c1 == &graph[0], L"&c1 != sorted[0]");
            Assert::IsTrue(&c0 == &graph[1], L"&c0 != sorted[1]");
        }
    }

    TEST_METHOD(noDependencies) {
        MemoryGuard guard;
        {
            SharedPointer<ValueConstraint> c0 = ghnew ValueConstraint(0.0f), c1 = ghnew ValueConstraint(0.0f);
            ConstraintGraph graph;
            graph.addAll({ &c0, &c1 });
            graph.sort();
            Assert::IsTrue(&c0 == &graph[0], L"&c0 != sorted[0]");
            Assert::IsTrue(&c1 == &graph[1], L"&c1 != sorted[1]");
        }
    }

    TEST_METHOD(cycles) {
        MemoryGuard guard;
        {
            SharedPointer<Constraint> c0 = ghnew Constraint(), c1 = ghnew Constraint(), c2 = ghnew Constraint(), c3 = ghnew Constraint();
            c3->Dependencies.add(&c3);
            c2->Dependencies.add(&c3);
            c2->Dependencies.add(&c0);
            c1->Dependencies.add(&c2);
            c0->Dependencies.add(&c1);
            c0->Dependencies.add(&c2);
            ConstraintGraph graph;
            graph.addAll({ &c0, &c1, &c2, &c3 });
            Assert::ExpectException<InvalidDataException>([&] {
                graph.sort();
            });
        }
    }

    TEST_METHOD(noCycles) {
        MemoryGuard guard;
        {
            SharedPointer<Constraint> c0 = ghnew Constraint(), c1 = ghnew Constraint(), c2 = ghnew Constraint(), c3 = ghnew Constraint();
            c2->Dependencies.add(&c3);
            c1->Dependencies.add(&c2);
            c0->Dependencies.add(&c1);
            c0->Dependencies.add(&c2);
            ConstraintGraph graph;
            graph.addAll({ &c0, &c1, &c2, &c3 });
            graph.sort();
            Assert::IsTrue(&c3 == &graph[0], L"&c3 != sorted[0]");
            Assert::IsTrue(&c2 == &graph[1], L"&c2 != sorted[1]");
            Assert::IsTrue(&c1 == &graph[2], L"&c1 != sorted[2]");
            Assert::IsTrue(&c0 == &graph[3], L"&c0 != sorted[3]");
        }
    }

    TEST_METHOD(wrapFill) {
        MemoryGuard guard;
        {
            SharedPointer<WrapWidthConstraint> wrap = ghnew WrapWidthConstraint();
            SharedPointer<Constraint> fill = ghnew Constraint();
            SharedPointer<ValueConstraint> value = ghnew ValueConstraint(0.0f);
            wrap->Dependencies.add(&fill);
            wrap->Dependencies.add(&value);
            fill->Dependencies.add(&wrap);
            ConstraintGraph graph;
            graph.addAll({ &wrap, &fill, &value });
            graph.sort();
            Assert::IsTrue(&value == &graph[0], L"&value != sorted[0]");
            Assert::IsTrue(&wrap == &graph[1], L"&wrap != sorted[1]");
            Assert::IsTrue(&fill == &graph[2], L"&fill != sorted[2]");
        }
    }

    TEST_METHOD(wrapCenterHorizontal) {
        MemoryGuard guard;
        {
            SharedPointer<ColorView> colorView = ghnew ColorView();
            colorView->Constraints = ConstraintSet()
                .withLeft(0.0f)
                .withWidth(50.0f)
                .withRight(100.0f);
            ConstraintGraph graph;
            colorView->resolveConstraints(graph);
            graph.sort();
            graph.evaluate();
            Assert::AreEqual(25.0f, colorView->Left.Value);
            Assert::AreEqual(75.0f, colorView->Right.Value);
        }
    }
    };
}
