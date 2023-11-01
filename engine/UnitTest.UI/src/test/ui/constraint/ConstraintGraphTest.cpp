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
        if (Pointer::numberOfAllocatedPointers() > 0) {
            Pointer::dumpPointers();
            Assert::Fail();
        }
    }

    TEST_METHOD(simple) {
        MemoryGuard guard;
        {
            auto c0 = makeShared<ValueConstraint>(0.0f), c1 = makeShared<ValueConstraint>(0.0f);
            c0->Dependencies.put(c1.get());
            ConstraintGraph graph;
            graph.addAll({ c0.get(), c1.get() });
            graph.sort();
            Assert::IsTrue(c1.get() == &graph[0], L"&c1 != sorted[0]");
            Assert::IsTrue(c0.get() == &graph[1], L"&c0 != sorted[1]");
        }
    }

    TEST_METHOD(noDependencies) {
        MemoryGuard guard;
        {
            auto c0 = makeShared<ValueConstraint>(0.0f), c1 = makeShared<ValueConstraint>(0.0f);
            ConstraintGraph graph;
            graph.addAll({ c0.get(), c1.get() });
            graph.sort();
            Assert::IsTrue(c0.get() == &graph[0], L"&c0 != sorted[0]");
            Assert::IsTrue(c1.get() == &graph[1], L"&c1 != sorted[1]");
        }
    }

    TEST_METHOD(cycles) {
        MemoryGuard guard;
        {
            SharedPointer<Constraint> c0 = makeShared<Constraint>(), c1 = makeShared<Constraint>(), c2 = makeShared<Constraint>(), c3 = makeShared<Constraint>();
            c3->Dependencies.put(c3.get());
            c2->Dependencies.put(c3.get());
            c2->Dependencies.put(c0.get());
            c1->Dependencies.put(c2.get());
            c0->Dependencies.put(c1.get());
            c0->Dependencies.put(c2.get());
            ConstraintGraph graph;
            graph.addAll({ c0.get(), c1.get(), c2.get(), c3.get() });
            Assert::ExpectException<InvalidDataException>([&] {
                graph.sort();
            });
        }
    }

    TEST_METHOD(noCycles) {
        MemoryGuard guard;
        {
            SharedPointer<Constraint> c0 = makeShared<Constraint>(), c1 = makeShared<Constraint>(), c2 = makeShared<Constraint>(), c3 = makeShared<Constraint>();
            c2->Dependencies.put(c3.get());
            c1->Dependencies.put(c2.get());
            c0->Dependencies.put(c1.get());
            c0->Dependencies.put(c2.get());
            ConstraintGraph graph;
            graph.addAll({ c0.get(), c1.get(), c2.get(), c3.get() });
            graph.sort();
            Assert::IsTrue(c3.get() == &graph[0], L"&c3 != sorted[0]");
            Assert::IsTrue(c2.get() == &graph[1], L"&c2 != sorted[1]");
            Assert::IsTrue(c1.get() == &graph[2], L"&c1 != sorted[2]");
            Assert::IsTrue(c0.get() == &graph[3], L"&c0 != sorted[3]");
        }
    }

    TEST_METHOD(wrapFill) {
        MemoryGuard guard;
        {
            auto wrap = makeShared<WrapWidthConstraint>();
            auto fill = makeShared<Constraint>();
            auto value = makeShared<ValueConstraint>(0.0f);
            wrap->Dependencies.put(fill.get());
            wrap->Dependencies.put(value.get());
            fill->Dependencies.put(wrap.get());
            ConstraintGraph graph;
            graph.addAll({ wrap.get(), fill.get(), value.get() });
            graph.sort();
            Assert::IsTrue(value.get() == &graph[0], L"&value != sorted[0]");
            Assert::IsTrue(wrap.get() == &graph[1], L"&wrap != sorted[1]");
            Assert::IsTrue(fill.get() == &graph[2], L"&fill != sorted[2]");
        }
    }

    TEST_METHOD(wrapCenterHorizontal) {
        MemoryGuard guard;
        {
            auto colorView = makeShared<ColorView>();
            colorView->Constraints = {
                .left = 0.0f,
                .width = 50.0f,
                .right = 100.0f
            };
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
