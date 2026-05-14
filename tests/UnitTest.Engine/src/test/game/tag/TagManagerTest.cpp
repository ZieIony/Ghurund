#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/game/tag/TagManager.h"

#include "test/utils/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Engine;
    using namespace UnitTest::Utils;

    TEST_CLASS(TagManagerTest) {
public:

    TEST_METHOD(TagManager_registerTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");

            Assert::IsTrue(tagManager.containsTag("player"));
            Assert::IsTrue(tagManager.containsTag("player.state"));
            Assert::IsTrue(tagManager.containsTag("player.state.running"));
            Assert::AreEqual(3ull, tagManager.TagCount);
        }
    }

    TEST_METHOD(TagManager_registerLeafTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");
            tagManager.registerTag("player.state.walking");

            Assert::IsTrue(tagManager.containsTag("player"));
            Assert::IsTrue(tagManager.containsTag("player.state"));
            Assert::IsTrue(tagManager.containsTag("player.state.running"));
            Assert::IsTrue(tagManager.containsTag("player.state.walking"));
            Assert::AreEqual(4ull, tagManager.TagCount);
        }
    }

    TEST_METHOD(TagManager_unregisterLeafTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");
            tagManager.unregisterTag("player.state.running");

            Assert::IsTrue(tagManager.containsTag("player"));
            Assert::IsTrue(tagManager.containsTag("player.state"));
            Assert::IsFalse(tagManager.containsTag("player.state.running"));
            Assert::AreEqual(2ull, tagManager.TagCount);
        }
    }

    TEST_METHOD(TagManager_unregisterParentTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");
            tagManager.unregisterTag("player.state");

            Assert::IsTrue(tagManager.containsTag("player"));
            Assert::IsFalse(tagManager.containsTag("player.state"));
            Assert::IsFalse(tagManager.containsTag("player.state.running"));
            Assert::AreEqual(1ull, tagManager.TagCount);
        }
    }

    TEST_METHOD(TagManager_getTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player");

            Tag tag = tagManager.getTag("player");
            Tag tag2 = tagManager.getTag("player");

            Assert::IsTrue(tag == tag2);
            Assert::AreEqual(1ull, tagManager.TagCount);
        }
    }
    };
}
