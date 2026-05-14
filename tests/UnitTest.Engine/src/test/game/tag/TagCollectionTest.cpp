#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/game/tag/TagCollection.h"
#include "engine/game/tag/TagManager.h"

#include "test/utils/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Engine;
    using namespace UnitTest::Utils;

    TEST_CLASS(TagCollectionTest) {
public:

    TEST_METHOD(TagCollection_addTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");

            TagCollection tagCollection;
            tagCollection.add(tagManager.getTag("player"));
            tagCollection.add(tagManager.getTag("player.state"));

            Assert::AreEqual(2ull, tagCollection.TagCount);
            Assert::IsTrue(tagCollection.contains(tagManager.getTag("player")));
        }
    }

    TEST_METHOD(TagCollection_removeTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");

            TagCollection tagCollection;
            tagCollection.add(tagManager.getTag("player"));
            tagCollection.add(tagManager.getTag("player.state"));
            tagCollection.remove(tagManager.getTag("player"));

            Assert::AreEqual(1ull, tagCollection.TagCount);
            Assert::IsFalse(tagCollection.contains(tagManager.getTag("player")));
        }
    }

    TEST_METHOD(TagCollection_containsTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");

            TagCollection tagCollection;
            tagCollection.add(tagManager.getTag("player"));
            tagCollection.add(tagManager.getTag("player.state"));

            Assert::AreEqual(2ull, tagCollection.TagCount);
            Assert::IsTrue(tagCollection.contains(tagManager.getTag("player")));
            Assert::IsTrue(tagCollection.contains(tagManager.getTag("player.state")));

            tagCollection.remove(tagManager.getTag("player.state"));

            Assert::AreEqual(1ull, tagCollection.TagCount);
            Assert::IsTrue(tagCollection.contains(tagManager.getTag("player")));
            Assert::IsFalse(tagCollection.contains(tagManager.getTag("player.state")));
        }
    }

    TEST_METHOD(TagCollection_matchesTag) {
        MemoryGuard guard;
        {
            TagManager tagManager;
            tagManager.registerTag("player.state.running");

            TagCollection tagCollection;
            tagCollection.add(tagManager.getTag("player.state"));

            Assert::IsFalse(tagCollection.matches(tagManager.getTag("player")));
            Assert::IsTrue(tagCollection.matches(tagManager.getTag("player.state")));
            Assert::IsTrue(tagCollection.matches(tagManager.getTag("player.state.running")));
        }
    }
    };
}
