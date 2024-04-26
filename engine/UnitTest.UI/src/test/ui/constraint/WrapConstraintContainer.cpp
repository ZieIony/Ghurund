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
#include <ui/constraint/ConstraintLayout.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::UI;

	TEST_CLASS(WrapConstraintContainerTest) {
public:
	TEST_CLASS_INITIALIZE(classInitialize) {
		TestUtils::testClassInitialize();
	}

	TEST_METHOD_CLEANUP(methodCleanup) {
		TestUtils::testMethodCleanup();
	}

	TEST_METHOD(wrapEmpty) {
		MemoryGuard guard;
		{
			auto container = makeShared<ControlContainer>();

			auto controlGroup = makeShared<ConstraintLayout>();
			ConstraintSet constraints = ConstraintSet(ConstraintSetInitializer{
				.width = makeShared<WrapWidthConstraint>(),
				.height = makeShared<WrapHeightConstraint>()
			});
			controlGroup->Children.add(container.get(), constraints);

			ConstraintGraph graph;
			SharedPointer<ValueConstraint> width = makeShared<ValueConstraint>(100);
			SharedPointer<ValueConstraint> height = makeShared<ValueConstraint>(100);
			controlGroup->resolveConstraints(graph, *width.get(), *height.get());
			graph.sort();
			graph.evaluate();

			Assert::AreEqual(0.0f, constraints.Width.Value);
			Assert::AreEqual(0.0f, constraints.Height.Value);
		}
	}

	TEST_METHOD(wrapEmptyMinRatioOffset) {
		MemoryGuard guard;
		{
			auto container = makeShared<ControlContainer>();

			auto controlGroup = makeShared<ConstraintLayout>();
			ConstraintSet constraints = ConstraintSet(ConstraintSetInitializer{
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
			});
			controlGroup->Children.add(container.get(), constraints);

			ConstraintGraph graph;
			SharedPointer<ValueConstraint> width = makeShared<ValueConstraint>(100);
			SharedPointer<ValueConstraint> height = makeShared<ValueConstraint>(100);
			controlGroup->resolveConstraints(graph, *width.get(), *height.get());
			graph.sort();
			graph.evaluate();

			Assert::AreEqual(100.0f, constraints.Width.Value);
			Assert::AreEqual(75.0f, constraints.Height.Value);
		}
	}

	TEST_METHOD(wrapChild) {
		MemoryGuard guard;
		{
			auto child = makeShared<ColorView>();
			auto group = makeShared<ControlContainer>();
			group->Child = child.get();
			group->setConstraints({
				.width = 100.0f,
				.height = 75.0f
				});

			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(group.get(), makeConstraints({
				.width = makeShared<WrapWidthConstraint>(),
				.height = makeShared<WrapHeightConstraint>()
				}));

			ConstraintGraph graph;
			SharedPointer<ValueConstraint> width = makeShared<ValueConstraint>(100);
			SharedPointer<ValueConstraint> height = makeShared<ValueConstraint>(100);
			controlGroup->resolveConstraints(graph, *width.get(), *height.get());
			graph.sort();
			graph.evaluate();

			ConstraintSet& constraints = controlGroup->Children[controlGroup->Children.Size - 1].Constraints;

			Assert::AreEqual(100.0f, constraints.Width.Value);
			Assert::AreEqual(75.0f, constraints.Height.Value);
		}
	}

	TEST_METHOD(wrapChildFillMinRatioOffset) {
		MemoryGuard guard;
		{
			auto child = makeShared<ColorView>();

			auto group = makeShared<ControlContainer>();
			group->Child = child.get();
			group->setConstraints({
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
				});


			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(group.get(), makeConstraints({
				.width = makeShared<WrapWidthConstraint>(),
				.height = makeShared<WrapHeightConstraint>()
				}));

			ConstraintGraph graph;
			SharedPointer<ValueConstraint> width = makeShared<ValueConstraint>(100);
			SharedPointer<ValueConstraint> height = makeShared<ValueConstraint>(100);
			controlGroup->resolveConstraints(graph, *width.get(), *height.get());
			graph.sort();
			graph.evaluate();

			ConstraintSet& constraints = controlGroup->Children[controlGroup->Children.Size - 1].Constraints;

			Assert::AreEqual(0.0f, constraints.Width.Value);
			Assert::AreEqual(0.0f, constraints.Height.Value);
		}
	}
	};
}