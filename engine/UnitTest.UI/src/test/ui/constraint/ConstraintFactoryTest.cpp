#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include "test/TestLogOutput.h"

#include "ui/constraint/ConstraintFactory.h"
#include "test/ui/TestShapeFactory.h"
#include "test/ui/TestDrawableFactory.h"
#include "test/ui/TextFormatFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/constraint/ConstraintGraph.h"
#include <ui/constraint/SiblingConstraint.h>
#include <ui/constraint/ParentConstraint.h>
#include "ui/control/DrawableView.h"
#include <ui/text/TextDocument.h>
#include <ui/style/LayoutAttr.h>
#include <ui/control/ColorView.h>
#include <ui/control/ControlGroup.h>

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ConstraintFactoryTest) {
public:
    TEST_CLASS_INITIALIZE(classInitialize) {
        TestUtils::testClassInitialize();
    }

    TEST_METHOD_CLEANUP(methodCleanup) {
        TestUtils::testMethodCleanup();
    }

    TEST_METHOD(parseParent) {
        MemoryGuard memoryGuard;
        {
            ConstraintFactory factory;
            {
                IntrusivePointer<Constraint> parentLeft(dynamic_cast<ParentLeftConstraint*>(factory.parseConstraint("Parent.Left", Orientation::HORIZONTAL)));
                Assert::IsNotNull(&parentLeft);
            }
            {
                IntrusivePointer<Constraint> parentRight(dynamic_cast<ParentRightConstraint*>(factory.parseConstraint("Parent.Right", Orientation::HORIZONTAL)));
                Assert::IsNotNull(&parentRight);
            }
            {
                IntrusivePointer<Constraint> parentTop(dynamic_cast<ParentTopConstraint*>(factory.parseConstraint("Parent.Top", Orientation::VERTICAL)));
                Assert::IsNotNull(&parentTop);
            }
            {
                IntrusivePointer<Constraint> parentBottom(dynamic_cast<ParentBottomConstraint*>(factory.parseConstraint("Parent.Bottom", Orientation::VERTICAL)));
                Assert::IsNotNull(&parentBottom);
            }
            {
                IntrusivePointer<Constraint> parentWidth(dynamic_cast<ParentWidthConstraint*>(factory.parseConstraint("Parent.Width", Orientation::HORIZONTAL)));
                Assert::IsNotNull(&parentWidth);
            }
            {
                IntrusivePointer<Constraint> parentHeight(dynamic_cast<ParentHeightConstraint*>(factory.parseConstraint("Parent.Height", Orientation::VERTICAL)));
                Assert::IsNotNull(&parentHeight);
            }
        }
    }

    TEST_METHOD(parseSibling) {
        MemoryGuard memoryGuard;
        {
            ConstraintFactory factory;
            {
                IntrusivePointer<SiblingLeftConstraint> siblingLeft(dynamic_cast<SiblingLeftConstraint*>(factory.parseConstraint("'color'.Left", Orientation::HORIZONTAL)));
                Assert::IsNotNull(&siblingLeft);
                Assert::AreEqual(AString("color"), siblingLeft->Name);
            }
            {
                IntrusivePointer<SiblingRightConstraint> siblingRight(dynamic_cast<SiblingRightConstraint*>(factory.parseConstraint("'color'.Right", Orientation::HORIZONTAL)));
                Assert::IsNotNull(&siblingRight);
                Assert::AreEqual(AString("color"), siblingRight->Name);
            }
            {
                IntrusivePointer<SiblingTopConstraint> siblingTop(dynamic_cast<SiblingTopConstraint*>(factory.parseConstraint("'color'.Top", Orientation::VERTICAL)));
                Assert::IsNotNull(&siblingTop);
                Assert::AreEqual(AString("color"), siblingTop->Name);
            }
            {
                IntrusivePointer<SiblingBottomConstraint> siblingBottom(dynamic_cast<SiblingBottomConstraint*>(factory.parseConstraint("'color'.Bottom", Orientation::VERTICAL)));
                Assert::IsNotNull(&siblingBottom);
                Assert::AreEqual(AString("color"), siblingBottom->Name);
            }
            {
                IntrusivePointer<SiblingWidthConstraint> siblingWidth(dynamic_cast<SiblingWidthConstraint*>(factory.parseConstraint("'color'.Width", Orientation::HORIZONTAL)));
                Assert::IsNotNull(&siblingWidth);
                Assert::AreEqual(AString("color"), siblingWidth->Name);
            }
            {
                IntrusivePointer<SiblingHeightConstraint> siblingHeight(dynamic_cast<SiblingHeightConstraint*>(factory.parseConstraint("'color'.Height", Orientation::VERTICAL)));
                Assert::IsNotNull(&siblingHeight);
                Assert::AreEqual(AString("color"), siblingHeight->Name);
            }
        }
    }

    TEST_METHOD(parseXml) {
        Ghurund::Core::getType<bool>();
        Ghurund::Core::getType<uint32_t>();
        Ghurund::Core::getType<float>();
        Ghurund::Core::getType<const AString&>();
        Ghurund::Core::getType<const AString*>();
        Ghurund::Core::getType<const WString&>();
        Ghurund::Core::getType<const ColorAttr&>();
        Ghurund::Core::getType<std::unique_ptr<ColorAttr>>();
        Ghurund::Core::getType<Ghurund::UI::ImageScaleMode>();
        Ghurund::Core::getType<Shape>();
        Ghurund::Core::getType<ColorView>();
        Ghurund::Core::getType<std::unique_ptr<Shape>>();
        Ghurund::Core::getType<std::unique_ptr<Ghurund::UI::DrawableAttr>>();
        Ghurund::Core::getType<std::unique_ptr<TextDocument>>();
        Ghurund::Core::getType<std::unique_ptr<LayoutAttr>>();

#ifdef _DEBUG
        RefCountedObject::reservePointers(1500);
        RefCountedObject::setPointersListResizeLocked(true);
#endif
        MemoryGuard memoryGuard;
        {
            ResourceManager resourceManager;
            TestShapeFactory shapeFactory;
            TestDrawableFactory drawableFactory;
            TextFormatFactory textFormatFactory;
            ConstraintFactory constraintFactory;
            auto layoutLoader = makeIntrusive<LayoutLoader>(resourceManager, shapeFactory, drawableFactory, textFormatFactory, constraintFactory);
            resourceManager.Loaders.set<Control>(layoutLoader.get());

            IntrusivePointer<ControlGroup> controlGroup(resourceManager.load<ControlGroup>(FilePath(_T("ConstraintFactoryTest.xml")), DirectoryPath(), ResourceFormat::AUTO, LoadOption::DONT_CACHE));
            Control* control = controlGroup->find<ColorView>();

            ConstraintSet& constraints = controlGroup->getConstraints(*control);
            Assert::IsNotNull(dynamic_cast<ValueConstraint*>(&constraints.Left));
            Assert::AreEqual(5.0f, constraints.Left.Value);

            Assert::IsNotNull(dynamic_cast<ValueConstraint*>(&constraints.Top));
            Assert::AreEqual(3.0f, constraints.Top.Value);

            ConstraintGraph graph;
            IntrusivePointer<ValueConstraint> width = makeIntrusive<ValueConstraint>(100.0f);
            IntrusivePointer<ValueConstraint> height = makeIntrusive<ValueConstraint>(100.0f);
            controlGroup->resolveConstraints(graph, *width.get(), *height.get());
            graph.sort();
            graph.evaluate();

            Assert::AreEqual(34.0f, constraints.Width.Value);
        }
#ifdef _DEBUG
        RefCountedObject::setPointersListResizeLocked(false);
#endif
    }
    };
}
