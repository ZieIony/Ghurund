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

using namespace Ghurund::UI;
using namespace UnitTest::Utils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(TextDocumentTest) {
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

    TEST_METHOD(parseXml) {
        Pointer::reservePointers(300);
        MemoryGuard memoryGuard;
        {
            ResourceManager resourceManager;
            ShapeFactory shapeFactory;
            ImageDrawableFactory imageDrawableFactory;
            TextFormatFactory textFormatFactory;
            ConstraintFactory constraintFactory;
            LayoutLoader* layoutLoader = ghnew LayoutLoader(resourceManager, shapeFactory, imageDrawableFactory, textFormatFactory, constraintFactory);
            resourceManager.Loaders.set<Control>(std::unique_ptr<LayoutLoader>(layoutLoader));

            SharedPointer<Control> control(resourceManager.load<Control>(FilePath(_T("TextDocumentTest.xml")), nullptr, LoadOption::DONT_CACHE));
        }
    }
    };
}
