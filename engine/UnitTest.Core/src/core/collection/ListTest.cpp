#include "pch.h"
#include "CppUnitTest.h"
#include "TestAllocator.h"
#include "MemoryGuard.h"

#include "core/collection/List.h"
#include "core/collection/Stack.h"
#include "core/Timer.h"

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

    TEST_CLASS(ListTest) {
public:

    TEST_METHOD(List_constructor) {
        MemoryGuard guard;
        {
            TestAllocator a;
            List<uint32_t, TestAllocator&> list(a);

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, true);
            Assert::AreEqual(a.Allocations, 1);
        }

        {
            List<TestClass> list;

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, true);
        }
    }

    TEST_METHOD(List_constructorInitial) {
        MemoryGuard guard;
        {
            List<uint32_t> list(20);

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity, (size_t)20);
            Assert::AreEqual(list.Empty, true);
        }

        {
            List<TestClass> list(20);

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity, (size_t)20);
            Assert::AreEqual(list.Empty, true);
        }
    }

    TEST_METHOD(List_constructorCopy) {
        MemoryGuard guard;
        {
            List<uint32_t> testList = { 1, 2, 3 };
            List<uint32_t> list = List<uint32_t>(testList);

            Assert::AreEqual(list.Size, (size_t)3ull);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_constructorMove) {
        MemoryGuard guard;
        {
            List<uint32_t> testList = { 1, 2, 3 };
            List<uint32_t> list = std::move(testList);

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_constructorInitializer) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_referenceAssignment) {
        MemoryGuard guard;
        {
            Stack<uint32_t> testStack = { 1, 2, 3 };
            List<uint32_t> list;
            list = testStack;

            Assert::AreEqual(list.Size, testStack.Size);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_listReferenceAssignment) {
        MemoryGuard guard;
        {
            List<uint32_t> testList = { 1, 2, 3 };
            List<uint32_t> list;
            list = testList;

            Assert::AreEqual(list.Size, testList.Size);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_moveAssignment) {
        MemoryGuard guard;
        {
            List<uint32_t> testList = { 1, 2, 3 };
            List<uint32_t> list;
            list = std::move(testList);

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_initializerAssignment) {
        MemoryGuard guard;
        {
            List<uint32_t> list;
            list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_add) {
        MemoryGuard guard;
        {
            List<uint32_t> list;
            list.add(1);

            Assert::AreEqual(list.Size, (size_t)1);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
        }
    }

    TEST_METHOD(List_addAll_initializer) {
        MemoryGuard guard;
        {
            List<uint32_t> list;
            list.addAll({ 1, 2, 3 });

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_addAll_List) {
        MemoryGuard guard;
        {
            List<uint32_t> list;
            const List<uint32_t> testList = { 1, 2, 3 };
            list.addAll(testList);

            Assert::AreEqual(testList.Size, (size_t)3);
            Assert::AreEqual(testList.Capacity >= list.Size, true);
            Assert::AreEqual(testList.Empty, false);
            Assert::AreEqual(testList[0], 1u);
            Assert::AreEqual(testList[1], 2u);
            Assert::AreEqual(testList[2], 3u);

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);

            Assert::AreEqual(list.Size, testList.Size);
        }
    }

    TEST_METHOD(List_insert) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };
            list.insert(1, 4);

            Assert::AreEqual(list.Size, (size_t)4);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 4u);
            Assert::AreEqual(list[2], 2u);
            Assert::AreEqual(list[3], 3u);
        }
    }

    TEST_METHOD(List_set) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };
            list.set(1, 4);

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 4u);
            Assert::AreEqual(list[2], 3u);
        }
    }

    TEST_METHOD(List_get) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };
            auto val = list.get(1);

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            Assert::AreEqual(val, 2u);
        }

        {
            List<uint32_t> list2 = { 1, 2, 3 };
            const uint32_t& val2 = list2.get(1);
        }
    }

    TEST_METHOD(List_arrayOperator) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };
            uint32_t& val = list[1];

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            Assert::AreEqual(val, 2u);

            // does it compile with const?
            const List<uint32_t> list2 = { 1, 2, 3 };
            const uint32_t& val2 = list2[1];
        }
    }

    TEST_METHOD(List_remove) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };
            list.remove(2);

            Assert::AreEqual(list.Size, (size_t)2);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 3u);
        }
    }

    TEST_METHOD(List_removeAt) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };
            list.removeAt(2);

            Assert::AreEqual(list.Size, (size_t)2);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
        }
    }

    TEST_METHOD(List_removeAll_initializer) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3,4,5,6,7,8 };
            list.removeAll({ 2,4,1 });

            Assert::AreEqual(list.Size, (size_t)5);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);

            List<uint32_t> testList = { 3,5,6,7,8 };
            size_t i = 0;
            for (auto& item : list)
                Assert::AreEqual(item, testList[i++]);
        }
    }
    TEST_METHOD(List_iterator) {
        MemoryGuard guard;
        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            List<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);

            size_t i = 0;
            for (auto& item : list)
                Assert::AreEqual(item, testVector[i++]);
        }

        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            const List<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);

            size_t i = 0;
            for (auto& item : list)
                Assert::AreEqual(item, testVector[i++]);
        }
    }

    TEST_METHOD(List_indexOf) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list.indexOf(2), (size_t)1);
            Assert::AreEqual(list.indexOf(4), (size_t)3);
        }

        {
            const List<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list.indexOf(2), (size_t)1);
            Assert::AreEqual(list.indexOf(4), (size_t)3);
        }
    }

    TEST_METHOD(List_contains) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::IsTrue(list.contains(1));
            Assert::IsFalse(list.contains(4));
        }

        {
            const List<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::IsTrue(list.contains(1));
            Assert::IsFalse(list.contains(4));
        }
    }

    TEST_METHOD(List_comparison) {
        MemoryGuard guard;
        {
            List<uint32_t> list = { 1, 2, 3 };
            List<uint32_t> list2 = { 1, 2, 3 };

            Assert::AreEqual(list.Size, (size_t)3);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, false);
            Assert::IsTrue(list == list2);
        }
    }

    TEST_METHOD(List_performance) {
        Timer timer;
        timer.tick();
        List<uint32_t> list;
        for (uint32_t i = 0; i < 100000; i++)
            list.add(i);
        timer.tick();
        auto timeList = timer.FrameTimeMs;
        timer.tick();
        std::vector<uint32_t> vector;
        for (uint32_t i = 0; i < 100000; i++)
            vector.push_back(i);
        timer.tick();
        auto timeVector = timer.FrameTimeMs;
        Assert::IsTrue(timeList < timeVector);
    }
    };
}
