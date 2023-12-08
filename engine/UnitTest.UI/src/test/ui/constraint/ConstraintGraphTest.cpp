#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include "test/TestLogOutput.h"

#include "ui/control/ColorView.h"
#include "ui/constraint/Constraint.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/constraint/WrapConstraint.h"
#include "ui/constraint/ParentConstraint.h"

#include <format>

using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Ghurund::Core;
using namespace Ghurund::UI;

namespace UnitTest {
	TEST_CLASS(ConstraintGraphTest) {
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

	TEST_METHOD(simple) {
		MemoryGuard guard;
		{
			auto c0 = makeShared<ValueConstraint>(0.0f), c1 = makeShared<ValueConstraint>(0.0f);
			c0->Dependencies.put(c1.get());
			ConstraintGraph graph;
			graph.addAll({ c0.get(), c1.get() });
			graph.sort();
			Assert::IsTrue(graph.validateOrder({ c1.get(), c0.get() }), L"incorrect constraint order");
		}
	}

	TEST_METHOD(noDependencies) {
		MemoryGuard guard;
		{
			auto c0 = makeShared<ValueConstraint>(0.0f), c1 = makeShared<ValueConstraint>(0.0f);
			ConstraintGraph graph;
			graph.addAll({ c0.get(), c1.get() });
			graph.sort();
			Assert::IsTrue(graph.validateOrder({ c0.get(), c1.get() }), L"incorrect constraint order");
		}
	}

	TEST_METHOD(cycles) {
		MemoryGuard guard;
		{
			SharedPointer<ValueConstraint> c0 = makeShared<ValueConstraint>(), c1 = makeShared<ValueConstraint>(), c2 = makeShared<ValueConstraint>(), c3 = makeShared<ValueConstraint>();
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
			SharedPointer<ValueConstraint> c0 = makeShared<ValueConstraint>(), c1 = makeShared<ValueConstraint>(), c2 = makeShared<ValueConstraint>(), c3 = makeShared<ValueConstraint>();
			c2->Dependencies.put(c3.get());
			c1->Dependencies.put(c2.get());
			c0->Dependencies.put(c1.get());
			c0->Dependencies.put(c2.get());
			ConstraintGraph graph;
			graph.addAll({ c0.get(), c1.get(), c2.get(), c3.get() });
			graph.sort();
			Assert::IsTrue(graph.validateOrder({ c3.get(), c2.get(), c1.get(), c0.get() }), L"incorrect constraint order");
		}
	}

	TEST_METHOD(wrapFill) {
		MemoryGuard guard;
		{
			auto wrap = makeShared<WrapWidthConstraint>();
			auto fill = makeShared<ParentWidthConstraint>();
			auto value = makeShared<ValueConstraint>(0.0f);
			wrap->Dependencies.put(fill.get());
			wrap->Dependencies.put(value.get());
			fill->Dependencies.put(wrap.get());
			ConstraintGraph graph;
			graph.addAll({ wrap.get(), fill.get(), value.get() });
			graph.sort();
			Assert::IsTrue(graph.validateOrder({ value.get(), wrap.get(), fill.get() }), L"incorrect constraint order");
		}
	}

	TEST_METHOD(wrapRightFill) {
		MemoryGuard guard;
		{
			auto wrap = makeShared<WrapWidthConstraint>();
			SharedPointer<Constraint> fill(ghnew ParentWidthConstraint());
			SharedPointer<Constraint> left(ghnew ValueConstraint(1.0f));
			auto right = makeShared<LeftWidthConstraint>(left, fill);
			auto value = makeShared<ValueConstraint>(0.0f);
			wrap->Dependencies.put(left.get());
			wrap->Dependencies.put(right.get());
			wrap->Dependencies.put(value.get());
			fill->Dependencies.put(wrap.get());
			ConstraintGraph graph;
			graph.addAll({ wrap.get(), left.get(), fill.get(), right.get(), value.get() });
			graph.sort();
			Ghurund::Core::Logger::print(LogType::INFO, graph.print().Data);
			Assert::IsTrue(graph.validateOrder({ left.get(), wrap.get(), fill.get(), right.get() }), L"invalid constraint order");
			Assert::IsTrue(graph.validateOrder({ value.get(), wrap.get(), fill.get(), right.get() }), L"invalid constraint order");
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
