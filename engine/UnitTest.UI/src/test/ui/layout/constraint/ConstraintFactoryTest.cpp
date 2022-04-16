#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"

#include "ui/layout/constraint/ConstraintFactory.h"

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ConstraintFactoryTest) {
public:

    TEST_METHOD(parseParent) {
        ConstraintFactory factory;
        {
            Constraint* parentLeft = dynamic_cast<ParentLeftConstraint*>(factory.parseConstraint("Parent.Left", Orientation::HORIZONTAL));
            Assert::IsNotNull(parentLeft);
        }
        {
            Constraint* parentRight = dynamic_cast<ParentRightConstraint*>(factory.parseConstraint("Parent.Right", Orientation::HORIZONTAL));
            Assert::IsNotNull(parentRight);
        }
        {
            Constraint* parentTop = dynamic_cast<ParentTopConstraint*>(factory.parseConstraint("Parent.Top", Orientation::VERTICAL));
            Assert::IsNotNull(parentTop);
        }
        {
            Constraint* parentBottom = dynamic_cast<ParentBottomConstraint*>(factory.parseConstraint("Parent.Bottom", Orientation::VERTICAL));
            Assert::IsNotNull(parentBottom);
        }
        {
            Constraint* parentWidth = dynamic_cast<ParentWidthConstraint*>(factory.parseConstraint("Parent.Width", Orientation::HORIZONTAL));
            Assert::IsNotNull(parentWidth);
        }
        {
            Constraint* parentHeight = dynamic_cast<ParentHeightConstraint*>(factory.parseConstraint("Parent.Height", Orientation::VERTICAL));
            Assert::IsNotNull(parentHeight);
        }
    }

    TEST_METHOD(parseSibling) {
        ConstraintFactory factory;
        {
            auto* siblingLeft = dynamic_cast<SiblingLeftConstraint*>(factory.parseConstraint("'color'.Left", Orientation::HORIZONTAL));
            Assert::IsNotNull(siblingLeft);
            Assert::AreEqual(AString("color"), siblingLeft->Name);
        }
        {
            auto* siblingRight = dynamic_cast<SiblingRightConstraint*>(factory.parseConstraint("'color'.Right", Orientation::HORIZONTAL));
            Assert::IsNotNull(siblingRight);
            Assert::AreEqual(AString("color"), siblingRight->Name);
        }
        {
            auto* siblingTop = dynamic_cast<SiblingTopConstraint*>(factory.parseConstraint("'color'.Top", Orientation::VERTICAL));
            Assert::IsNotNull(siblingTop);
            Assert::AreEqual(AString("color"), siblingTop->Name);
        }
        {
            auto* siblingBottom = dynamic_cast<SiblingBottomConstraint*>(factory.parseConstraint("'color'.Bottom", Orientation::VERTICAL));
            Assert::IsNotNull(siblingBottom);
            Assert::AreEqual(AString("color"), siblingBottom->Name);
        }
        {
            auto* siblingWidth = dynamic_cast<SiblingWidthConstraint*>(factory.parseConstraint("'color'.Width", Orientation::HORIZONTAL));
            Assert::IsNotNull(siblingWidth);
            Assert::AreEqual(AString("color"), siblingWidth->Name);
        }
        {
            auto* siblingHeight = dynamic_cast<SiblingHeightConstraint*>(factory.parseConstraint("'color'.Height", Orientation::VERTICAL));
            Assert::IsNotNull(siblingHeight);
            Assert::AreEqual(AString("color"), siblingHeight->Name);
        }
    }
    };
}
