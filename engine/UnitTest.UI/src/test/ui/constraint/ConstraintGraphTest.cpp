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
#include <ui/constraint/ConstraintLayout.h>
#include <ui/constraint/SelfConstraint.h>

using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Ghurund::Core;
using namespace Ghurund::UI;

namespace UnitTest {
	TEST_CLASS(ConstraintGraphTest) {
public:
	TEST_CLASS_INITIALIZE(classInitialize) {
		TestUtils::testClassInitialize();
	}

	TEST_METHOD_CLEANUP(methodCleanup) {
		TestUtils::testMethodCleanup();
	}

	TEST_METHOD(simple) {
		MemoryGuard guard;
		{
			auto c0 = makeIntrusive<ValueConstraint>(0.0f), c1 = makeIntrusive<ValueConstraint>(0.0f);
			c0->Dependencies.put(c1.get());
			ConstraintGraph graph;
			graph.addAll({ c0.get(), c1.get() });
			graph.sort();
#if defined _DEBUG || defined GH_TEST
			Assert::IsTrue(graph.validateOrder({ c1.get(), c0.get() }), L"incorrect constraint order");
#endif
		}
	}

	TEST_METHOD(noDependencies) {
		MemoryGuard guard;
		{
			auto c0 = makeIntrusive<ValueConstraint>(0.0f), c1 = makeIntrusive<ValueConstraint>(0.0f);
			ConstraintGraph graph;
			graph.addAll({ c0.get(), c1.get() });
			graph.sort();
#if defined _DEBUG || defined GH_TEST
			Assert::IsTrue(graph.validateOrder({ c0.get(), c1.get() }), L"incorrect constraint order");
#endif
		}
	}

	TEST_METHOD(cycles) {
		MemoryGuard guard;
		{
			IntrusivePointer<ValueConstraint> c0 = makeIntrusive<ValueConstraint>(), c1 = makeIntrusive<ValueConstraint>(), c2 = makeIntrusive<ValueConstraint>(), c3 = makeIntrusive<ValueConstraint>();
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
			IntrusivePointer<ValueConstraint> c0 = makeIntrusive<ValueConstraint>(), c1 = makeIntrusive<ValueConstraint>(), c2 = makeIntrusive<ValueConstraint>(), c3 = makeIntrusive<ValueConstraint>();
			c2->Dependencies.put(c3.get());
			c1->Dependencies.put(c2.get());
			c0->Dependencies.put(c1.get());
			c0->Dependencies.put(c2.get());
			ConstraintGraph graph;
			graph.addAll({ c0.get(), c1.get(), c2.get(), c3.get() });
			graph.sort();
#if defined _DEBUG || defined GH_TEST
			Assert::IsTrue(graph.validateOrder({ c3.get(), c2.get(), c1.get(), c0.get() }), L"incorrect constraint order");
#endif
		}
	}

	TEST_METHOD(wrapFill) {
		MemoryGuard guard;
		{
			auto wrap = makeIntrusive<WrapWidthConstraint>();
			auto fill = makeIntrusive<ParentWidthConstraint>();
			auto value = makeIntrusive<ValueConstraint>(0.0f);
			wrap->Dependencies.put(fill.get());
			wrap->Dependencies.put(value.get());
			fill->Dependencies.put(wrap.get());
			ConstraintGraph graph;
			graph.addAll({ wrap.get(), fill.get(), value.get() });
			graph.sort();
#if defined _DEBUG || defined GH_TEST
			Assert::IsTrue(graph.validateOrder({ value.get(), wrap.get(), fill.get() }), L"incorrect constraint order");
#endif
		}
	}

	TEST_METHOD(wrapRightFill) {
		MemoryGuard guard;
		{
			auto wrap = makeIntrusive<WrapWidthConstraint>();
			IntrusivePointer<Constraint> fill(ghnew ParentWidthConstraint());
			IntrusivePointer<Constraint> left(ghnew ValueConstraint(1.0f));
			auto right = makeIntrusive<LeftWidthConstraint>(left, fill);
			auto value = makeIntrusive<ValueConstraint>(0.0f);
			wrap->Dependencies.put(left.get());
			wrap->Dependencies.put(right.get());
			wrap->Dependencies.put(value.get());
			fill->Dependencies.put(wrap.get());
			ConstraintGraph graph;
			graph.addAll({ wrap.get(), left.get(), fill.get(), right.get(), value.get() });
			graph.sort();
#if defined _DEBUG || defined GH_TEST
			Ghurund::Core::Logger::print(LogType::INFO, graph.print().Data);
			Assert::IsTrue(graph.validateOrder({ left.get(), wrap.get(), fill.get(), right.get() }), L"invalid constraint order");
			Assert::IsTrue(graph.validateOrder({ value.get(), wrap.get(), fill.get(), right.get() }), L"invalid constraint order");
#endif
		}
	}

	TEST_METHOD(wrapCenterHorizontal) {
		MemoryGuard guard;
		{
			auto colorView = makeIntrusive<ColorView>();

			auto controlGroup = makeIntrusive<ConstraintLayout>();
			controlGroup->Children.add(colorView.get(), makeConstraints({
				.left = 0.0f,
				.width = 50.0f,
				.right = 100.0f
			}));
			ConstraintSet& constraints = controlGroup->Children.get(1).Constraints;
		
			ConstraintGraph graph;
			IntrusivePointer<ValueConstraint> width = makeIntrusive<ValueConstraint>(100.0f);
			IntrusivePointer<ValueConstraint> height = makeIntrusive<ValueConstraint>(100.0f);
			controlGroup->resolveConstraints(graph, *width.get(), *height.get());
			graph.sort();
			graph.evaluate();
			Assert::AreEqual(25.0f, constraints.Left.Value);
			Assert::AreEqual(75.0f, constraints.Right.Value);
		}
	}
	};
}
