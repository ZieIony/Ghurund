#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include "test/TestLogOutput.h"

#include "ui/constraint/ConstraintFactory.h"
#include "test/ui/ShapeFactory.h"
#include "test/ui/ImageDrawableFactory.h"
#include "test/ui/TextFormatFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/constraint/ConstraintGraph.h"
#include <ui/constraint/SiblingConstraint.h>
#include <ui/constraint/ParentConstraint.h>
#include "ui/control/ColorView.h"
#include <ui/control/ControlGroup.h>
#include "ui/layout/LayoutManager.h"
#include <ui/constraint/ConstraintLayout.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::UI;

	TEST_CLASS(ConstraintSetTest) {
public:
	TEST_CLASS_INITIALIZE(classInitialize) {
		TestUtils::testClassInitialize();
	}

	TEST_METHOD_CLEANUP(methodCleanup) {
		TestUtils::testMethodCleanup();
	}

	TEST_METHOD(passConstraintSet) {
		Pointer::reservePointers(300);
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto left = makeShared<ValueConstraint>(0.0f);
			auto width = makeShared<ValueConstraint>(0.0f);
			auto right = makeShared<ValueConstraint>(0.0f);

			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(control.get(), ConstraintSet(ConstraintSetInitializer{
				.left = left,
				.width = width,
				.right = right
				}));
		}
	}

	TEST_METHOD(setAllWidth) {
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto left = makeShared<ValueConstraint>(0.0f);
			auto width = makeShared<ValueConstraint>(0.0f);
			auto right = makeShared<ValueConstraint>(0.0f);

			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(control.get(), ConstraintSet(ConstraintSetInitializer{
				.left = left,
				.width = width,
				.right = right
				}));
			ConstraintSet& constraints = controlGroup->Children[controlGroup->Children.Size - 1].Constraints;

			Assert::IsNotNull(dynamic_cast<CenterLeftConstraint*>(&constraints.Left));
			Assert::AreEqual(3ul, left->ReferenceCount);
			Assert::IsTrue(width.get() == &constraints.Width);
			Assert::AreEqual(4ul, width->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<CenterRightConstraint*>(&constraints.Right));
			Assert::AreEqual(3ul, right->ReferenceCount);

			Assert::IsNotNull(&constraints.Top);
			Assert::AreEqual(2ul, constraints.Top.ReferenceCount);
			Assert::IsNotNull(&constraints.Height);
			Assert::AreEqual(2ul, constraints.Height.ReferenceCount);
			Assert::IsNotNull(&constraints.Bottom);
			Assert::AreEqual(1ul, constraints.Bottom.ReferenceCount);
		}
	}

	TEST_METHOD(setAllHeight) {
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto top = makeShared<ValueConstraint>(0.0f);
			auto height = makeShared<ValueConstraint>(0.0f);
			auto bottom = makeShared<ValueConstraint>(0.0f);

			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(control.get(), makeConstraints({
				.top = top,
				.height = height,
				.bottom = bottom
				}));
			ConstraintSet& constraints = controlGroup->Children[controlGroup->Children.Size - 1].Constraints;

			Assert::IsNotNull(&constraints.Left);
			Assert::AreEqual(2ul, constraints.Left.ReferenceCount);
			Assert::IsNotNull(&constraints.Width);
			Assert::AreEqual(2ul, constraints.Width.ReferenceCount);
			Assert::IsNotNull(&constraints.Right);
			Assert::AreEqual(1ul, constraints.Right.ReferenceCount);

			Assert::IsNotNull(dynamic_cast<CenterTopConstraint*>(&constraints.Top));
			Assert::AreEqual(3ul, top->ReferenceCount);
			Assert::IsTrue(height.get() == &constraints.Height);
			Assert::AreEqual(4ul, height->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<CenterBottomConstraint*>(&constraints.Bottom));
			Assert::AreEqual(3ul, bottom->ReferenceCount);
		}
	}

	TEST_METHOD(setLeftWidthTopHeight) {
		Pointer::reservePointers(300);
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto left = makeShared<ValueConstraint>(0.0f);
			auto width = makeShared<ValueConstraint>(0.0f);
			auto top = makeShared<ValueConstraint>(0.0f);
			auto height = makeShared<ValueConstraint>(0.0f);

			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(control.get(), makeConstraints({
				.left = left,
				.width = width,
				.top = top,
				.height = height
				}));
			ConstraintSet& constraints = controlGroup->Children[controlGroup->Children.Size - 1].Constraints;

			Assert::IsTrue(left.get() == &constraints.Left);
			Assert::AreEqual(3ul, constraints.Left.ReferenceCount);
			Assert::IsTrue(width.get() == &constraints.Width);
			Assert::AreEqual(3ul, constraints.Width.ReferenceCount);
			Assert::IsNotNull(dynamic_cast<LeftWidthConstraint*>(&constraints.Right));
			Assert::AreEqual(1ul, constraints.Right.ReferenceCount);

			Assert::IsTrue(top.get() == &constraints.Top);
			Assert::AreEqual(3ul, top->ReferenceCount);
			Assert::IsTrue(height.get() == &constraints.Height);
			Assert::AreEqual(3ul, height->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<TopHeightConstraint*>(&constraints.Bottom));
			Assert::AreEqual(1ul, constraints.Bottom.ReferenceCount);
		}
	}

	TEST_METHOD(setLeftRightTopBottom) {
		Pointer::reservePointers(300);
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto left = makeShared<ValueConstraint>(0.0f);
			auto right = makeShared<ValueConstraint>(0.0f);
			auto top = makeShared<ValueConstraint>(0.0f);
			auto bottom = makeShared<ValueConstraint>(0.0f);

			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(control.get(), makeConstraints({
				.left = left,
				.right = right,
				.top = top,
				.bottom = bottom
				}));
			ConstraintSet& constraints = controlGroup->Children[controlGroup->Children.Size - 1].Constraints;

			Assert::IsTrue(left.get() == &constraints.Left);
			Assert::AreEqual(3ul, constraints.Left.ReferenceCount);
			Assert::IsNotNull(dynamic_cast<LeftRightConstraint*>(&constraints.Width));
			Assert::AreEqual(1ul, constraints.Width.ReferenceCount);
			Assert::IsTrue(right.get() == &constraints.Right);
			Assert::AreEqual(3ul, constraints.Right.ReferenceCount);

			Assert::IsTrue(top.get() == &constraints.Top);
			Assert::AreEqual(3ul, top->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<TopBottomConstraint*>(&constraints.Height));
			Assert::AreEqual(1ul, constraints.Height.ReferenceCount);
			Assert::IsTrue(bottom.get() == &constraints.Bottom);
			Assert::AreEqual(3ul, bottom->ReferenceCount);
		}
	}

	TEST_METHOD(setWidthRightHeightBottom) {
		Pointer::reservePointers(300);
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto width = makeShared<ValueConstraint>(0.0f);
			auto right = makeShared<ValueConstraint>(0.0f);
			auto height = makeShared<ValueConstraint>(0.0f);
			auto bottom = makeShared<ValueConstraint>(0.0f);

			auto controlGroup = makeShared<ConstraintLayout>();
			controlGroup->Children.add(control.get(), makeConstraints({
				.width = width,
				.right = right,
				.height = height,
				.bottom = bottom
				}));
			ConstraintSet& constraints = controlGroup->Children[controlGroup->Children.Size - 1].Constraints;

			Assert::IsNotNull(dynamic_cast<WidthRightConstraint*>(&constraints.Left));
			Assert::AreEqual(1ul, constraints.Left.ReferenceCount);
			Assert::IsTrue(width.get() == &constraints.Width);
			Assert::AreEqual(3ul, constraints.Width.ReferenceCount);
			Assert::IsTrue(right.get() == &constraints.Right);
			Assert::AreEqual(3ul, constraints.Right.ReferenceCount);

			Assert::IsNotNull(dynamic_cast<HeightBottomConstraint*>(&constraints.Top));
			Assert::AreEqual(1ul, constraints.Top.ReferenceCount);
			Assert::IsTrue(height.get() == &constraints.Height);
			Assert::AreEqual(3ul, height->ReferenceCount);
			Assert::IsTrue(bottom.get() == &constraints.Bottom);
			Assert::AreEqual(3ul, bottom->ReferenceCount);
		}
	}
	};
}
