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
#include "ui/control/ControlGroup.h"
#include <ui/control/ColorView.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::UI;

	TEST_CLASS(WrapConstraintGroupTest) {
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
			auto group = makeShared<ControlGroup>();
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

	TEST_METHOD(wrapEmptyMinRatioOffset) {
		MemoryGuard guard;
		{
			auto group = makeShared<ControlGroup>();
			group->Constraints = {
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
			auto child1 = makeShared<ColorView>();
			child1->Constraints = {
				.width = 100.0f,
				.height = 75.0f
			};

			auto child2 = makeShared<ColorView>();
			child2->Constraints = {
				.width = 150.0f,
				.height = 50.0f
			};

			auto group = makeShared<ControlGroup>();
			group->Children.addAll({ child1.get(), child2.get() });
			group->Constraints = {
				.width = makeShared<WrapWidthConstraint>(),
				.height = makeShared<WrapHeightConstraint>()
			};

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
			auto child1 = makeShared<ColorView>();
			child1->Constraints = {
				.width = 100.0f,
				.height = 75.0f
			};
			auto child2 = makeShared<ColorView>();
			child2->Constraints = {
				.width = makeShared<ParentWidthConstraint>(),
				.height = makeShared<ParentHeightConstraint>()
			};

			auto group = makeShared<ControlGroup>();
			group->Children.addAll({ child1.get(), child2.get() });
			group->Constraints = {
				.width = makeShared<WrapWidthConstraint>(),
				.height = makeShared<WrapHeightConstraint>()
			};

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

	TEST_METHOD(wrapChildrenComplexOffset) {
		MemoryGuard guard;
		{
			auto child1 = makeShared<ColorView>();
			child1->Constraints = {
				.width = makeShared<ParentWidthConstraint>(),
				.height = makeShared<ParentHeightConstraint>()
			};
			auto child2 = makeShared<ColorView>();
			child2->Constraints = {
				.left = [] {
						auto constraint = makeShared<ParentLeftConstraint>();
						constraint->Offset = 8;
						return constraint;
					}(),
				.width = 150.0f,
				.top = [] {
						auto constraint = makeShared<ParentTopConstraint>();
						constraint->Offset = 4;
						return constraint;
					}(),
				.height = 50.0f
			};

			auto group = makeShared<ControlGroup>();
			group->Children.addAll({ child1.get(), child2.get() });
			group->Constraints = {
				.width = [] {
						auto constraint = makeShared<WrapWidthConstraint>();
						constraint->Offset = 8;
						return constraint;
					}(),
				.height = [] {
						auto constraint = makeShared<WrapHeightConstraint>();
						constraint->Offset = 4;
						return constraint;
					}()
			};

			ConstraintGraph graph;
			group->resolveConstraints(graph);
			graph.sort();
			graph.evaluate();

			Assert::AreEqual(158.0f, child2->Right.Value);
			Assert::AreEqual(54.0f, child2->Bottom.Value);
			Assert::AreEqual(166.0f, group->Width.Value);
			Assert::AreEqual(58.0f, group->Height.Value);

			graph.clear();
			group->resolveConstraints(graph);
			graph.sort();
			graph.evaluate();

			Assert::AreEqual(158.0f, child2->Right.Value);
			Assert::AreEqual(54.0f, child2->Bottom.Value);
			Assert::AreEqual(166.0f, group->Width.Value);
			Assert::AreEqual(58.0f, group->Height.Value);
		}
	}

	TEST_METHOD(wrapChildrenFillMinRatioOffset) {
		MemoryGuard guard;
		{
			auto child1 = makeShared<ColorView>();
			child1->Constraints = {
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
			auto child2 = makeShared<ColorView>();
			child2->Constraints = {
				.width = []() {
					auto c = makeShared<WrapWidthConstraint>();
					c->Min = 150;
					c->Ratio = 0.5f;
					c->Offset = 10.0f;
					return c;
				}(),
				.height = []() {
					auto c = makeShared<WrapHeightConstraint>();
					c->Min = 50;
					c->Ratio = 0.5f;
					c->Offset = 10.0f;
					return c;
				}()
			};

			auto group = makeShared<ControlGroup>();
			group->Children.addAll({ child1.get(), child2.get() });
			group->Constraints = {
				.width = makeShared<WrapWidthConstraint>(),
				.height = makeShared<WrapHeightConstraint>()
			};

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