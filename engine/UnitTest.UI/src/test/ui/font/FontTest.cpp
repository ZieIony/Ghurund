#include "pch.h"
#include "CppUnitTest.h"

#include "core/image/ImageLoader.h"
#include "core/io/DirectoryLibrary.h"
#include "ui/font/Font.h"
#include "ui/font/FontLoader.h"

#include "test/TestLogOutput.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;
    using namespace UnitTest::Utils;

    TEST_CLASS(FontTest) {
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

    TEST_METHOD(Font_init) {
        ResourceManager resourceManager;
        SharedPointer<FontLoader> fontLoader;
        SharedPointer<ImageLoader> imageLoader;
        fontLoader.set(ghnew FontLoader());
        imageLoader.set(ghnew ImageLoader());
        resourceManager.Loaders.set<Font>(fontLoader.get());
        resourceManager.Loaders.set<Image>(imageLoader.get());
        resourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"../../resources")));

        auto latoMediumPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_bold.ttf");
        SharedPointer<Font> font = makeShared<Font>();
        Ghurund::Core::SharedPointer<Ghurund::UI::Font> latoMediumFont(resourceManager.load<Ghurund::UI::Font>(latoMediumPath, DirectoryPath()));
        //resourceManager.save(*latoMediumFont.get()->Atlas, FilePath(_T("../../test.bmp")));
    }
    };
}
