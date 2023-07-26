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

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::UI;

	TEST_CLASS(ConstraintSetTest) {
public:
	TEST_CLASS_INITIALIZE(classInitialize) {
		Ghurund::Core::Logger::init(std::make_unique<TestLogOutput>());
		TestLogOutput::initReportHook();
	}

	TEST_METHOD_CLEANUP(methodCleanup) {
		if (Pointer::numberOfAllocatedPointers() > 0) {
			Pointer::dumpPointers();
			Assert::Fail();
		}
	}

	TEST_METHOD(passConstraintSet) {
		Pointer::reservePointers(300);
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto left = makeShared<ValueConstraint>(0.0f);
			auto width = makeShared<ValueConstraint>(0.0f);
			auto right = makeShared<ValueConstraint>(0.0f);
			control->Constraints = {
				.left = left,
				.width = width,
				.right = right
			};
		}
	}

	TEST_METHOD(setAllWidth) {
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto left = makeShared<ValueConstraint>(0.0f);
			auto width = makeShared<ValueConstraint>(0.0f);
			auto right = makeShared<ValueConstraint>(0.0f);

			control->Constraints = {
				.left = left,
				.width = width,
				.right = right
			};

			Assert::IsNotNull(dynamic_cast<CenterLeftConstraint*>(&control->Left));
			Assert::AreEqual(3ul, left->ReferenceCount);
			Assert::IsTrue(width.get() == &control->Width);
			Assert::AreEqual(4ul, width->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<CenterRightConstraint*>(&control->Right));
			Assert::AreEqual(3ul, right->ReferenceCount);

			Assert::IsNotNull(&control->Top);
			Assert::AreEqual(2ul, control->Top.ReferenceCount);
			Assert::IsNotNull(&control->Height);
			Assert::AreEqual(2ul, control->Height.ReferenceCount);
			Assert::IsNotNull(&control->Bottom);
			Assert::AreEqual(1ul, control->Bottom.ReferenceCount);
		}
	}

	TEST_METHOD(setAllHeight) {
		MemoryGuard memoryGuard;
		{
			auto control = makeShared<ColorView>();
			auto top = makeShared<ValueConstraint>(0.0f);
			auto height = makeShared<ValueConstraint>(0.0f);
			auto bottom = makeShared<ValueConstraint>(0.0f);

			control->Constraints = {
				.top = top,
				.height = height,
				.bottom = bottom
			};

			Assert::IsNotNull(&control->Left);
			Assert::AreEqual(2ul, control->Left.ReferenceCount);
			Assert::IsNotNull(&control->Width);
			Assert::AreEqual(2ul, control->Width.ReferenceCount);
			Assert::IsNotNull(&control->Right);
			Assert::AreEqual(1ul, control->Right.ReferenceCount);

			Assert::IsNotNull(dynamic_cast<CenterTopConstraint*>(&control->Top));
			Assert::AreEqual(3ul, top->ReferenceCount);
			Assert::IsTrue(height.get() == &control->Height);
			Assert::AreEqual(4ul, height->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<CenterBottomConstraint*>(&control->Bottom));
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

			control->Constraints = ConstraintSet{
				.left = left,
				.width = width,
				.top = top,
				.height = height
			};

			Assert::IsTrue(left.get() == &control->Left);
			Assert::AreEqual(3ul, control->Left.ReferenceCount);
			Assert::IsTrue(width.get() == &control->Width);
			Assert::AreEqual(3ul, control->Width.ReferenceCount);
			Assert::IsNotNull(dynamic_cast<LeftWidthConstraint*>(&control->Right));
			Assert::AreEqual(1ul, control->Right.ReferenceCount);

			Assert::IsTrue(top.get() == &control->Top);
			Assert::AreEqual(3ul, top->ReferenceCount);
			Assert::IsTrue(height.get() == &control->Height);
			Assert::AreEqual(3ul, height->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<TopHeightConstraint*>(&control->Bottom));
			Assert::AreEqual(1ul, control->Bottom.ReferenceCount);
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

			control->Constraints = {
				.left = left,
				.right = right,
				.top = top,
				.bottom = bottom
			};

			Assert::IsTrue(left.get() == &control->Left);
			Assert::AreEqual(3ul, control->Left.ReferenceCount);
			Assert::IsNotNull(dynamic_cast<LeftRightConstraint*>(&control->Width));
			Assert::AreEqual(1ul, control->Width.ReferenceCount);
			Assert::IsTrue(right.get() == &control->Right);
			Assert::AreEqual(3ul, control->Right.ReferenceCount);

			Assert::IsTrue(top.get() == &control->Top);
			Assert::AreEqual(3ul, top->ReferenceCount);
			Assert::IsNotNull(dynamic_cast<TopBottomConstraint*>(&control->Height));
			Assert::AreEqual(1ul, control->Height.ReferenceCount);
			Assert::IsTrue(bottom.get() == &control->Bottom);
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

			control->Constraints = {
				.width = width,
				.right = right,
				.height = height,
				.bottom = bottom
			};

			Assert::IsNotNull(dynamic_cast<WidthRightConstraint*>(&control->Left));
			Assert::AreEqual(1ul, control->Left.ReferenceCount);
			Assert::IsTrue(width.get() == &control->Width);
			Assert::AreEqual(3ul, control->Width.ReferenceCount);
			Assert::IsTrue(right.get() == &control->Right);
			Assert::AreEqual(3ul, control->Right.ReferenceCount);

			Assert::IsNotNull(dynamic_cast<HeightBottomConstraint*>(&control->Top));
			Assert::AreEqual(1ul, control->Top.ReferenceCount);
			Assert::IsTrue(height.get() == &control->Height);
			Assert::AreEqual(3ul, height->ReferenceCount);
			Assert::IsTrue(bottom.get() == &control->Bottom);
			Assert::AreEqual(3ul, bottom->ReferenceCount);
		}
	}
	};
}
