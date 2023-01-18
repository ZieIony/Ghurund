#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"

#include "ui/layout/constraint/ConstraintFactory.h"
#include "test/ui/ShapeFactory.h"
#include "test/ui/ImageDrawableFactory.h"
#include "test/ui/TextFormatFactory.h"
#include "ui/loading/LayoutLoader.h"
#include <ui/layout/constraint/ConstraintSolver.h>

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
            Constraint* parentLeft = dynamic_cast<ParentLeftConstraint*>(factory.parseConstraint("Parent.Left"));
            Assert::IsNotNull(parentLeft);
        }
        {
            Constraint* parentRight = dynamic_cast<ParentRightConstraint*>(factory.parseConstraint("Parent.Right"));
            Assert::IsNotNull(parentRight);
        }
        {
            Constraint* parentTop = dynamic_cast<ParentTopConstraint*>(factory.parseConstraint("Parent.Top"));
            Assert::IsNotNull(parentTop);
        }
        {
            Constraint* parentBottom = dynamic_cast<ParentBottomConstraint*>(factory.parseConstraint("Parent.Bottom"));
            Assert::IsNotNull(parentBottom);
        }
        {
            Constraint* parentWidth = dynamic_cast<ParentWidthConstraint*>(factory.parseConstraint("Parent.Width"));
            Assert::IsNotNull(parentWidth);
        }
        {
            Constraint* parentHeight = dynamic_cast<ParentHeightConstraint*>(factory.parseConstraint("Parent.Height"));
            Assert::IsNotNull(parentHeight);
        }
    }

    TEST_METHOD(parseSibling) {
        ConstraintFactory factory;
        {
            auto* siblingLeft = dynamic_cast<SiblingLeftConstraint*>(factory.parseConstraint("'color'.Left"));
            Assert::IsNotNull(siblingLeft);
            Assert::AreEqual(AString("color"), siblingLeft->Name);
        }
        {
            auto* siblingRight = dynamic_cast<SiblingRightConstraint*>(factory.parseConstraint("'color'.Right"));
            Assert::IsNotNull(siblingRight);
            Assert::AreEqual(AString("color"), siblingRight->Name);
        }
        {
            auto* siblingTop = dynamic_cast<SiblingTopConstraint*>(factory.parseConstraint("'color'.Top"));
            Assert::IsNotNull(siblingTop);
            Assert::AreEqual(AString("color"), siblingTop->Name);
        }
        {
            auto* siblingBottom = dynamic_cast<SiblingBottomConstraint*>(factory.parseConstraint("'color'.Bottom"));
            Assert::IsNotNull(siblingBottom);
            Assert::AreEqual(AString("color"), siblingBottom->Name);
        }
        {
            auto* siblingWidth = dynamic_cast<SiblingWidthConstraint*>(factory.parseConstraint("'color'.Width"));
            Assert::IsNotNull(siblingWidth);
            Assert::AreEqual(AString("color"), siblingWidth->Name);
        }
        {
            auto* siblingHeight = dynamic_cast<SiblingHeightConstraint*>(factory.parseConstraint("'color'.Height"));
            Assert::IsNotNull(siblingHeight);
            Assert::AreEqual(AString("color"), siblingHeight->Name);
        }
    }

    TEST_METHOD(parseXml) {
        ResourceManager resourceManager;
        ShapeFactory shapeFactory;
        ImageDrawableFactory imageDrawableFactory;
        TextFormatFactory textFormatFactory;
        ConstraintFactory constraintFactory;
        LayoutLoader* layoutLoader = ghnew LayoutLoader(resourceManager, shapeFactory, imageDrawableFactory, textFormatFactory, constraintFactory);
        resourceManager.Loaders.set<Control>(std::unique_ptr<LayoutLoader>(layoutLoader));

        auto* control = resourceManager.load<Control>(FilePath(_T("ConstraintFactoryTest.xml")));

        Assert::IsNotNull(dynamic_cast<ValueConstraint*>(&control->Left));
        Assert::AreEqual(5.0f, control->Left.Value);

        Assert::IsNotNull(dynamic_cast<ValueConstraint*>(&control->Top));
        Assert::AreEqual(3.0f, control->Top.Value);

        List<Constraint*> constraints;
        control->resolveConstraints(constraints);
        ConstraintSolver solver;
        solver.sortGraph(constraints);
        for (Constraint* c : constraints)
            c->evaluate();

        Assert::AreEqual(34.0f, control->Width.Value);
    }
    };
}
