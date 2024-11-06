#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include <test/TestLogOutput.h>
#include "test/ui/TestControlContainer.h"

#include "ui/constraint/ParentConstraint.h"
#include "ui/control/ControlGroup.h"
#include <ui/control/ControlContainer.h>
#include <ui/control/DrawableView.h>
#include <test/ui/image/TestImage.h>
#include <test/ui/TestDrawableFactory.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::UI;

	TEST_CLASS(ParentSizeConstraintTest) {
public:
	TEST_CLASS_INITIALIZE(classInitialize) {
#ifdef _DEBUG
		RefCountedObject::reservePointers(500);
#endif
		Ghurund::Core::Logger::init(std::make_unique<TestLogOutput>());
		TestLogOutput::initReportHook();
	}

	TEST_METHOD_CLEANUP(methodCleanup) {
#ifdef _DEBUG
		if (RefCountedObject::numberOfAllocatedPointers() > 0) {
			RefCountedObject::dumpPointers();
			Assert::Fail();
		}
#endif
	}

	TEST_METHOD(parentSizeValue) {
		MemoryGuard guard;
		{
			auto root = makeIntrusive<TestControlContainer>();
			auto group = makeIntrusive<ControlGroup>();
			root->Child = group.get();
			root->setConstraints(*group.get(), {
				.width = 100.0f,
				.height = 80.0f
				});
			auto child = makeIntrusive<ControlGroup>();
			group->Children.add(child.get(), makeConstraints({
				.width = makeIntrusive<ParentWidthConstraint>(),
				.height = makeIntrusive<ParentHeightConstraint>()
				}));

			root->resolveConstraints();

			Assert::AreEqual(100.0f, group->getConstraints(*child.get()).Width.Value);
			Assert::AreEqual(80.0f, group->getConstraints(*child.get()).Height.Value);
		}
	}

	TEST_METHOD(parentSizeContent) {
		MemoryGuard guard;
		{
			auto root = makeIntrusive<TestControlContainer>();
			Theme theme;
			root->Theme = &theme;
			auto group = makeIntrusive<ControlGroup>();
			root->Child = group.get();
			root->setConstraints(*group.get(), {
				.width = makeIntrusive<ContentWidthConstraint>(),
				.height = makeIntrusive<ContentHeightConstraint>()
				});
			auto child = makeIntrusive<DrawableView>();
			auto drawable = makeIntrusive<TestImage>();
			drawable->setPreferredSize({ 50.0f, 40.0f });
			child->Drawable = drawable.get();
			group->Children.add(child.get(), makeConstraints({
				.width = makeIntrusive<ParentWidthConstraint>(),
				.height = makeIntrusive<ParentHeightConstraint>()
				}));

			root->resolveConstraints();

			Assert::AreEqual(50.0f, root->getConstraints(*group.get()).Width.Value);
			Assert::AreEqual(40.0f, root->getConstraints(*group.get()).Height.Value);
			Assert::AreEqual(50.0f, group->getConstraints(*child.get()).Width.Value);
			Assert::AreEqual(40.0f, group->getConstraints(*child.get()).Height.Value);
		}
	}

	};
}
