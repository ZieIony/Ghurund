#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/utils/TestUtils.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestLogOutput.h"
#include "test/ui/UITestUtils.h"

#include "ui/constraint/ConstraintFactory.h"
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
	using namespace UnitTest::Utils;

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
			auto container = makeIntrusive<ControlContainer>();

			auto controlGroup = makeIntrusive<ConstraintLayout>();
			ConstraintSet constraints = makeConstraints({
				.width = makeIntrusive<ContentWidthConstraint>(),
				.height = makeIntrusive<ContentHeightConstraint>()
			});
			controlGroup->Children.add(container.get(), constraints);

			layoutControl(controlGroup, 100.0f, 100.0f);

			Assert::AreEqual(0.0f, container->Size.Width);
			Assert::AreEqual(0.0f, container->Size.Height);
		}
	}

	TEST_METHOD(wrapEmptyMinRatioOffset) {
		MemoryGuard guard;
		{
			auto container = makeIntrusive<ControlContainer>();

			auto controlGroup = makeIntrusive<ConstraintLayout>();
			ConstraintSet constraints = makeConstraints({
				.width = [] {
					auto c = makeIntrusive<WrapWidthConstraint>();
					c->Min = 100;
					c->Ratio = 0.5f;
					c->Offset = 10.0f;
					return c;
				}(),
				.height = [] {
					auto c = makeIntrusive<WrapHeightConstraint>();
					c->Min = 75;
					c->Ratio = 0.5f;
					c->Offset = 10.0f;
					return c;
				}()
			});
			controlGroup->Children.add(container.get(), constraints);

			layoutControl(controlGroup, 100.0f, 100.0f);

			Assert::AreEqual(100.0f, container->Size.Width);
			Assert::AreEqual(75.0f, container->Size.Height);
		}
	}

	TEST_METHOD(wrapChild) {
		MemoryGuard guard;
		{
			auto child = makeIntrusive<ColorView>();
			auto group = makeIntrusive<ControlContainer>();
			group->Child = child.get();
			group->setConstraints(*child.get(), makeConstraints({
				.width = 100.0f,
				.height = 75.0f
				}));

			auto controlGroup = makeIntrusive<ConstraintLayout>();
			ConstraintSet constraints = makeConstraints({
				.width = makeIntrusive<WrapWidthConstraint>(),
				.height = makeIntrusive<WrapHeightConstraint>()
				});
			controlGroup->Children.add(group.get(), constraints);

			layoutControl(controlGroup, 100.0f, 100.0f);

			Assert::AreEqual(100.0f, group->Size.Width);
			Assert::AreEqual(75.0f, group->Size.Height);
		}
	}

	TEST_METHOD(wrapChildFillMinRatioOffset) {
		MemoryGuard guard;
		{
			auto child = makeIntrusive<ColorView>();

			auto group = makeIntrusive<ControlContainer>();
			group->setChild(child.get(), makeConstraints({
				.width = [] {
					auto c = makeIntrusive<ParentWidthConstraint>();
					c->Min = 100.0f;
					c->Ratio = 0.5f;
					c->Offset = 10.0f;
					return c;
				}(),
				.height = [] {
					auto c = makeIntrusive<ParentHeightConstraint>();
					c->Min = 75.0f;
					c->Ratio = 0.5f;
					c->Offset = 10.0f;
					return c;
				}()
				}));


			auto controlGroup = makeIntrusive<ConstraintLayout>();
			controlGroup->Children.add(group.get(), makeConstraints({
				.width = makeIntrusive<WrapWidthConstraint>(),
				.height = makeIntrusive<WrapHeightConstraint>()
				}));

			layoutControl(controlGroup, 100.0f, 100.0f);

			Assert::AreEqual(0.0f, group->Size.Width);
			Assert::AreEqual(0.0f, group->Size.Height);
		}
	}
	};
}