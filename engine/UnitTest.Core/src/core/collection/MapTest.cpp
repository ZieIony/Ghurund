#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/string/String.h"
#include "TestAllocator.h"
#include "MemoryGuard.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;
    using namespace std;

    struct TestClass {
        uint32_t val = 5;
        const char* text = "text";
    };

    TEST_CLASS(MapTest) {
public:

    TEST_METHOD(Map_constructor) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> map;

            Assert::AreEqual(map.Size, (size_t)0);
            Assert::AreEqual(map.Empty, true);
        }

        {
            Map<uint32_t, TestClass> map;

            Assert::AreEqual(map.Size, (size_t)0);
            Assert::AreEqual(map.Empty, true);
        }
    }
    
    TEST_METHOD(Map_constructorCopy) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> testMap = { {1, "a"}, {2, "b"}, {3, "c"} };
            Map<uint32_t, AString> map = Map<uint32_t, AString>(testMap);

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));
        }
    }

    TEST_METHOD(Map_constructorMove) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> testMap = { {1, "a"}, {2, "b"}, {3, "c"} };
            Map<uint32_t, AString> map = std::move(testMap);

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));
        }
    }

    TEST_METHOD(Map_constructorInitializer) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));
        }
    }

    TEST_METHOD(Map_referenceAssignment_empty) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> testMap = { {1, "a"}, {2, "b"}, {3, "c"} };
            Map<uint32_t, AString> map;
            map = testMap;

            /*Assert::AreEqual(map.Size, testMap.Size);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));*/
        }
    }

    TEST_METHOD(Map_referenceAssignment_notEmpty) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> testMap = { {1, "a"}, {2, "b"}, {3, "c"} };
            Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };
            map = testMap;

            Assert::AreEqual(map.Size, testMap.Size);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));
        }
    }

    TEST_METHOD(Map_moveAssignment_empty) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> testMap = { {1, "a"}, {2, "b"}, {3, "c"} };
            Map<uint32_t, AString> map;
            map = std::move(testMap);

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));
        }
    }

    TEST_METHOD(Map_moveAssignment_notEmpty) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> testMap = { {1, "a"}, {2, "b"}, {3, "c"} };
            Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };
            map = std::move(testMap);

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));
        }
    }

    TEST_METHOD(Map_initializerAssignment) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> map;
            map = { {1, "a"}, {2, "b"}, {3, "c"} };

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsTrue(map.containsValue("b"));
            Assert::IsTrue(map.containsValue("c"));
        }
    }

    TEST_METHOD(Map_add) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> map;
            map.set(1, "a");

            Assert::AreEqual(map.Size, (size_t)1);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsValue("a"));
        }
    }

    TEST_METHOD(Map_remove) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> map = { {1, "a"},{ 2, "b"}, {3, "c"}, {5, "e"}, {20, "u"}, {4, "d"}, {7, "g"}, {14, "n"}, {22, "y"}, {6, "f"} };
            map.remove(2);
            map.remove(20);
            map.remove(7);
            map.remove(22);
            map.remove(1);
            map.remove(3);
            map.remove(5);
            map.remove(14);
            map.remove(6);
            map.remove(4);

            Assert::AreEqual(map.Size, (size_t)0);
            Assert::AreEqual(map.Empty, true);
            Assert::IsFalse(map.containsKey(1u));
            Assert::IsFalse(map.containsKey(2u));
            Assert::IsFalse(map.containsKey(3u));
        }
        {
            Map<uint32_t, AString> map = { {1, "a"}, {2, "b"} };
            map.remove(2);

            Assert::AreEqual(map.Size, (size_t)1);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsFalse(map.containsKey(2u));
        }
        {
            Map<uint32_t, AString> map = { {1, "a"} };
            map.remove(1);

            Assert::AreEqual(map.Size, (size_t)0);
            Assert::AreEqual(map.Empty, true);
            Assert::IsFalse(map.containsKey(1u));
        }
    }

    TEST_METHOD(Map_removeNonexisting) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };
            map.remove(4);

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1u));
            Assert::IsTrue(map.containsKey(2u));
            Assert::IsTrue(map.containsKey(3u));
            Assert::IsFalse(map.containsKey(4u));
        }
    }

    /*TEST_METHOD(Map_iterator) {
        {
            std::vector<uint32_t> testVector = { {1, "a"}, {2, "b"}, {3, "c"} };
            Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);

            size_t i = 0;
            for (auto& item : map)
                Assert::AreEqual(item, testVector[i++]);
        }

        {
            std::vector<uint32_t> testVector = { {1, "a"}, {2, "b"}, {3, "c"} };
            const Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);

            size_t i = 0;
            for (auto& item : map)
                Assert::AreEqual(item, testVector[i++]);
        }
        _____________________checkMemory();
    }*/

    TEST_METHOD(Map_contains) {
        MemoryGuard guard;
        {
            Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsFalse(map.containsKey(4));
            Assert::IsFalse(map.containsValue("d"));
        }

        {
            const Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };

            Assert::AreEqual(map.Size, (size_t)3);
            Assert::AreEqual(map.Empty, false);
            Assert::IsTrue(map.containsKey(1));
            Assert::IsTrue(map.containsValue("a"));
            Assert::IsFalse(map.containsKey(4));
            Assert::IsFalse(map.containsValue("d"));
        }
    }

    /*TEST_METHOD(Map_comparison) {
        Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };
        Map<uint32_t, AString> map2 = { {1, "a"}, {2, "b"}, {3, "c"} };

        Assert::AreEqual(map.Size, (size_t)3);
        Assert::AreEqual(map.Empty, false);
        Assert::IsTrue(map == map2);
        _____________________checkMemory();
    }*/
    };
}
