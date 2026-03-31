#include "utepch.h"
#include "CppUnitTest.h"

#include "core/Colors.h"
#include "core/io/File.h"
#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestUtils.h"
#include <core/coroutine/CoroutineScheduler.h>
#include <core/resource/ResourceManager.h>
#include <engine/audio/sound/Sound.h>
#include <engine/audio/sound/SoundLoader.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace std;

    TEST_CLASS(SoundTest) {
private:
    WString resDir = RES_DIR;

    Timer timer;
    CoroutineThreadPool threadPool = CoroutineThreadPool(4);
    CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
    ResourceManager resourceManager = coroutineScheduler;
    Audio audio;
    IntrusivePointer<SoundLoader> soundLoader = makeIntrusive<SoundLoader>(audio);

public:
    SoundTest() {
        TestUtils::testClassInitialize();

        audio.init();
        resourceManager.Loaders.set<Sound>(soundLoader.ref());
    }

    TEST_METHOD(Sound_emptyInvalidate) {
        MemoryGuard guard;
        {
            auto sound = makeIntrusive<Sound>();
            sound->invalidate();
        }
    }

    TEST_METHOD(Sound_doubleInvalidate) {
        MemoryGuard guard;
        {
			auto thudSound = IntrusivePointer(resourceManager.load<Sound>(
                FilePath(L"../../resources/test/sounds/thud.wav"),
                DirectoryPath(), ResourceFormat::AUTO, LoadOption::DONT_WATCH | LoadOption::DONT_CACHE
            ));
            thudSound->invalidate();
            thudSound->invalidate();
        }
    }
    };
}
