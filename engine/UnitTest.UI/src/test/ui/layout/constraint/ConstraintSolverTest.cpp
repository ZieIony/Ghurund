#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"

#include "ui/layout/constraint/Constraint.h"
#include "ui/layout/constraint/ConstraintSolver.h"
#include "ui/layout/constraint/ValueConstraint.h"
#include "ui/layout/constraint/WrapConstraint.h"

#include <format>
#include <ui/control/ColorView.h>

using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Ghurund::Core;
using namespace Ghurund::UI;

namespace UnitTest {
    TEST_CLASS(ConstraintSolverTest) {
public:

    TEST_METHOD(simple) {
        MemoryGuard guard;
        {
            ValueConstraint c0(0.0f), c1(0.0f);
            c0.Dependencies.add(&c1);
            List<Constraint*> constraints = { &c0, &c1 };
            List<Constraint*> sorted = ConstraintSolver::sortGraph(constraints);
            Assert::IsTrue(&c1 == sorted[0], L"&c1 != sorted[0]");
            Assert::IsTrue(&c0 == sorted[1], L"&c0 != sorted[1]");
        }
    }

    TEST_METHOD(noDependencies) {
        MemoryGuard guard;
        {
            ValueConstraint c0(0.0f), c1(0.0f);
            List<Constraint*> constraints = { &c0, &c1 };
            List<Constraint*> sorted = ConstraintSolver::sortGraph(constraints);
            Assert::IsTrue(&c0 == sorted[0], L"&c0 != sorted[0]");
            Assert::IsTrue(&c1 == sorted[1], L"&c1 != sorted[1]");
        }
    }

    TEST_METHOD(cycles) {
        MemoryGuard guard;
        {
            Constraint c0, c1, c2, c3;
            c3.Dependencies.add(&c3);
            c2.Dependencies.add(&c3);
            c2.Dependencies.add(&c0);
            c1.Dependencies.add(&c2);
            c0.Dependencies.add(&c1);
            c0.Dependencies.add(&c2);
            List<Constraint*> constraints = { &c0, &c1, &c2, &c3 };
            Assert::ExpectException<InvalidDataException>([&] {
                ConstraintSolver::sortGraph(constraints);
            });
        }
    }

    TEST_METHOD(noCycles) {
        MemoryGuard guard;
        {
            Constraint c0, c1, c2, c3;
            c2.Dependencies.add(&c3);
            c1.Dependencies.add(&c2);
            c0.Dependencies.add(&c1);
            c0.Dependencies.add(&c2);
            List<Constraint*> constraints = { &c0, &c1, &c2, &c3 };
            List<Constraint*> sorted = ConstraintSolver::sortGraph(constraints);
            Assert::IsTrue(&c3 == sorted[0], L"&c3 != sorted[0]");
            Assert::IsTrue(&c2 == sorted[1], L"&c2 != sorted[1]");
            Assert::IsTrue(&c1 == sorted[2], L"&c1 != sorted[2]");
            Assert::IsTrue(&c0 == sorted[3], L"&c0 != sorted[3]");
        }
    }

    TEST_METHOD(wrapFill) {
        MemoryGuard guard;
        {
            WrapConstraint wrap;
            Constraint fill;
            ValueConstraint value(0.0f);
            wrap.Dependencies.add(&fill);
            wrap.Dependencies.add(&value);
            fill.Dependencies.add(&wrap);
            List<Constraint*> constraints = { &wrap, &fill, &value };
            List<Constraint*> sorted = ConstraintSolver::sortGraph(constraints);
            Assert::IsTrue(&value == sorted[0], L"&value != sorted[0]");
            Assert::IsTrue(&wrap == sorted[1], L"&wrap != sorted[1]");
            Assert::IsTrue(&fill == sorted[2], L"&fill != sorted[2]");
        }
    }

    TEST_METHOD(wrapCenterHorizontal) {
        MemoryGuard guard;
        {
            SharedPointer<ColorView> colorView = ghnew ColorView();
            colorView->setConstraints({
                .left = std::make_shared<ValueConstraint>(0.0f),
                .width = std::make_shared<ValueConstraint>(50.0f),
                .right = std::make_shared<ValueConstraint>(100.0f)
                });
            List<Constraint*> constraints;
            colorView->resolveConstraints(constraints);
            List<Constraint*> sorted = ConstraintSolver::sortGraph(constraints);
            for (Constraint* c : sorted)
                c->evaluate();
            Assert::AreEqual(25.0f, colorView->Left.Value);
            Assert::AreEqual(75.0f, colorView->Right.Value);
        }
    }

    TEST_METHOD(bigGraph) {
        MemoryGuard guard;
        {
            Timer timer;
            List<Constraint*> constraints;
            for (size_t k = 0; k < 100; k++) {
                for (size_t i = 0; i < 20; i++) {
                    auto c = ghnew Constraint();
                    if (i > 10) {
                        for (size_t j = 1; j <= 3; j++)
                            c->Dependencies.add(constraints[i - j * 3]);
                    }
                    constraints.add(c);
                }
            }
            timer.tick();
            ConstraintSolver::sortGraph(constraints);
            timer.tick();
            constraints.deleteItems();
            uint32_t EXPECTED_SORT_TIME_MS = 5;
            Assert::IsTrue(timer.FrameTimeMs <= EXPECTED_SORT_TIME_MS, std::format(L"Sorting took more than {} ms ({} ms)", EXPECTED_SORT_TIME_MS, timer.FrameTimeMs).c_str());
        }
    }
    };
}
