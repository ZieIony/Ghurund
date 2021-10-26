#include "pch.h"
#include "CppUnitTest.h"

#include "core/resource/ResourceManager.h"
#include <core/resource/TextLoader.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;

    TEST_CLASS(ResourceManagerTest) {
private:
    ResourceManager resourceManager;

public:
    ResourceManagerTest() {
        resourceManager.Loaders.set<TextResource>(std::make_unique<TextLoader>());
        resourceManager.Libraries.add(ResourceManager::ENGINE_LIB_NAME, DirectoryPath(L"./resources"));
    }

    TEST_METHOD(ResourceManager_loadFileMissing) {
        //Ghurund::Core::SharedPointer<Font> latoMediumFont = resourceManager.load<Font>(Ghurund::Core::FilePath(L"lib://Ghurund/fonts\\lato_medium.ttf"));
    }
    };
}
