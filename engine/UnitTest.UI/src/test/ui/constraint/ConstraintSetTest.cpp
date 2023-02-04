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
        Pointer::dumpPointers();
    }

    TEST_METHOD(passConstraintSet) {
        MemoryGuard memoryGuard;
        {
            SharedPointer<Control> control = ghnew ColorView();
            SharedPointer<Constraint> left = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> width = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> right = ghnew ValueConstraint(0.0f);
            control->Constraints = ConstraintSet()
                .withLeft(left)
                .withWidth(width)
                .withRight(right);
        }
    }

    TEST_METHOD(setAllWidth) {
        MemoryGuard memoryGuard;
        {
            SharedPointer<Control> control = ghnew ColorView();
            SharedPointer<Constraint> left = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> width = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> right = ghnew ValueConstraint(0.0f);

            control->Constraints = ConstraintSet()
                .withLeft(left)
                .withWidth(width)
                .withRight(right);

            Assert::IsNotNull(dynamic_cast<CenterLeftConstraint*>(&control->Left));
            Assert::AreEqual(3ul, left->ReferenceCount);
            Assert::IsTrue(&width == &control->Width);
            Assert::AreEqual(4ul, width->ReferenceCount);
            Assert::IsNotNull(dynamic_cast<CenterRightConstraint*>(&control->Right));
            Assert::AreEqual(3ul, right->ReferenceCount);

            Assert::IsNotNull(&control->Top);
            Assert::AreEqual(1ul, control->Top.ReferenceCount);
            Assert::IsNotNull(&control->Height);
            Assert::AreEqual(1ul, control->Height.ReferenceCount);
            Assert::IsNotNull(&control->Bottom);
            Assert::AreEqual(1ul, control->Bottom.ReferenceCount);
        }
    }

    TEST_METHOD(setAllHeight) {
        MemoryGuard memoryGuard;
        {
            SharedPointer<Control> control = ghnew ColorView();
            SharedPointer<Constraint> top = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> height = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> bottom = ghnew ValueConstraint(0.0f);

            control->Constraints = ConstraintSet()
                .withTop(top)
                .withHeight(height)
                .withBottom(bottom);

            Assert::IsNotNull(&control->Left);
            Assert::AreEqual(1ul, control->Left.ReferenceCount);
            Assert::IsNotNull(&control->Width);
            Assert::AreEqual(1ul, control->Width.ReferenceCount);
            Assert::IsNotNull(&control->Right);
            Assert::AreEqual(1ul, control->Right.ReferenceCount);

            Assert::IsNotNull(dynamic_cast<CenterTopConstraint*>(&control->Top));
            Assert::AreEqual(3ul, top->ReferenceCount);
            Assert::IsTrue(&height == &control->Height);
            Assert::AreEqual(4ul, height->ReferenceCount);
            Assert::IsNotNull(dynamic_cast<CenterBottomConstraint*>(&control->Bottom));
            Assert::AreEqual(3ul, bottom->ReferenceCount);
        }
    }

    TEST_METHOD(setLeftWidthTopHeight) {
        MemoryGuard memoryGuard;
        {
            SharedPointer<Control> control = ghnew ColorView();
            SharedPointer<Constraint> left = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> width = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> top = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> height = ghnew ValueConstraint(0.0f);

            control->Constraints = ConstraintSet()
                .withLeft(left)
                .withWidth(width)
                .withTop(top)
                .withHeight(height);

            Assert::IsTrue(&left == &control->Left);
            Assert::AreEqual(2ul, control->Left.ReferenceCount);
            Assert::IsTrue(&width == &control->Width);
            Assert::AreEqual(2ul, control->Width.ReferenceCount);
            Assert::IsNotNull(dynamic_cast<LeftWidthConstraint*>(&control->Right));
            Assert::AreEqual(1ul, control->Right.ReferenceCount);

            Assert::IsTrue(&top == &control->Top);
            Assert::AreEqual(2ul, top->ReferenceCount);
            Assert::IsTrue(&height == &control->Height);
            Assert::AreEqual(2ul, height->ReferenceCount);
            Assert::IsNotNull(dynamic_cast<TopHeightConstraint*>(&control->Bottom));
            Assert::AreEqual(1ul, control->Bottom.ReferenceCount);
        }
    }

    TEST_METHOD(setLeftRightTopBottom) {
        MemoryGuard memoryGuard;
        {
            SharedPointer<Control> control = ghnew ColorView();
            SharedPointer<Constraint> left = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> right = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> top = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> bottom = ghnew ValueConstraint(0.0f);

            control->Constraints = ConstraintSet()
                .withLeft(left)
                .withRight(right)
                .withTop(top)
                .withBottom(bottom);

            Assert::IsTrue(&left == &control->Left);
            Assert::AreEqual(2ul, control->Left.ReferenceCount);
            Assert::IsNotNull(dynamic_cast<LeftRightConstraint*>(&control->Width));
            Assert::AreEqual(1ul, control->Width.ReferenceCount);
            Assert::IsTrue(&right == &control->Right);
            Assert::AreEqual(2ul, control->Right.ReferenceCount);

            Assert::IsTrue(&top == &control->Top);
            Assert::AreEqual(2ul, top->ReferenceCount);
            Assert::IsNotNull(dynamic_cast<TopBottomConstraint*>(&control->Height));
            Assert::AreEqual(1ul, control->Height.ReferenceCount);
            Assert::IsTrue(&bottom == &control->Bottom);
            Assert::AreEqual(2ul, bottom->ReferenceCount);
        }
    }

    TEST_METHOD(setWidthRightHeightBottom) {
        MemoryGuard memoryGuard;
        {
            SharedPointer<Control> control = ghnew ColorView();
            SharedPointer<Constraint> width = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> right = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> height = ghnew ValueConstraint(0.0f);
            SharedPointer<Constraint> bottom = ghnew ValueConstraint(0.0f);

            control->Constraints = ConstraintSet()
                .withWidth(width)
                .withRight(right)
                .withHeight(height)
                .withBottom(bottom);

            Assert::IsNotNull(dynamic_cast<WidthRightConstraint*>(&control->Left));
            Assert::AreEqual(1ul, control->Left.ReferenceCount);
            Assert::IsTrue(&width == &control->Width);
            Assert::AreEqual(2ul, control->Width.ReferenceCount);
            Assert::IsTrue(&right == &control->Right);
            Assert::AreEqual(2ul, control->Right.ReferenceCount);

            Assert::IsNotNull(dynamic_cast<HeightBottomConstraint*>(&control->Top));
            Assert::AreEqual(1ul, control->Top.ReferenceCount);
            Assert::IsTrue(&height == &control->Height);
            Assert::AreEqual(2ul, height->ReferenceCount);
            Assert::IsTrue(&bottom == &control->Bottom);
            Assert::AreEqual(2ul, bottom->ReferenceCount);
        }
    }
    };
}
