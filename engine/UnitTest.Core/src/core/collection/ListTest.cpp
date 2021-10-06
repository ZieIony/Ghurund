#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/List.h"
#include "core/collection/Stack.h"
#include "TestAllocator.h"

#include <iostream>
#include <vector>
#include <core/Timer.h>

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
        {
            TestAllocator a;
            List<uint32_t, TestAllocator&> list(a);

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, true);
            Assert::AreEqual(a.Allocations, 1);
        }
        _____________________checkMemory();

        {
            List<TestClass> list;

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity >= list.Size, true);
            Assert::AreEqual(list.Empty, true);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(List_constructorInitial) {
        {
            List<uint32_t> list(20);

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity, (size_t)20);
            Assert::AreEqual(list.Empty, true);
        }
        _____________________checkMemory();

        {
            List<TestClass> list(20);

            Assert::AreEqual(list.Size, (size_t)0);
            Assert::AreEqual(list.Capacity, (size_t)20);
            Assert::AreEqual(list.Empty, true);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(List_constructorCopy) {
        List<uint32_t> testList = { 1, 2, 3 };
        List<uint32_t> list = List<uint32_t>(testList);

        Assert::AreEqual(list.Size, (size_t)3ull);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_constructorMove) {
        List<uint32_t> testList = { 1, 2, 3 };
        List<uint32_t> list = std::move(testList);

        Assert::AreEqual(list.Size, (size_t)3);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_constructorInitializer) {
        List<uint32_t> list = { 1, 2, 3 };

        Assert::AreEqual(list.Size, (size_t)3);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_referenceAssignment) {
        Stack<uint32_t> testStack = { 1, 2, 3 };
        List<uint32_t> list;
        list = testStack;

        Assert::AreEqual(list.Size, testStack.Size);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_listReferenceAssignment) {
        List<uint32_t> testList = { 1, 2, 3 };
        List<uint32_t> list;
        list = testList;

        Assert::AreEqual(list.Size, testList.Size);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_moveAssignment) {
        List<uint32_t> testList = { 1, 2, 3 };
        List<uint32_t> list;
        list = std::move(testList);

        Assert::AreEqual(list.Size, (size_t)3);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_initializerAssignment) {
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
        _____________________checkMemory();
    }

    TEST_METHOD(List_add) {
        List<uint32_t> list;
        list.add(1);

        Assert::AreEqual(list.Size, (size_t)1);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_addAll_initializer) {
        List<uint32_t> list;
        list.addAll({ 1, 2, 3 });

        Assert::AreEqual(list.Size, (size_t)3);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_addAll_List) {
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
        _____________________checkMemory();
    }

    TEST_METHOD(List_insert) {
        List<uint32_t> list = { 1, 2, 3 };
        list.insert(1, 4);

        Assert::AreEqual(list.Size, (size_t)4);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 4u);
        Assert::AreEqual(list[2], 2u);
        Assert::AreEqual(list[3], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_set) {
        List<uint32_t> list = { 1, 2, 3 };
        list.set(1, 4);

        Assert::AreEqual(list.Size, (size_t)3);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 4u);
        Assert::AreEqual(list[2], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_get) {
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
        _____________________checkMemory();
    }

    TEST_METHOD(List_arrayOperator) {
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

        _____________________checkMemory();
    }

    TEST_METHOD(List_remove) {
        List<uint32_t> list = { 1, 2, 3 };
        list.remove(2);

        Assert::AreEqual(list.Size, (size_t)2);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_removeAt) {
        List<uint32_t> list = { 1, 2, 3 };
        list.removeAt(2);

        Assert::AreEqual(list.Size, (size_t)2);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::AreEqual(list[0], 1u);
        Assert::AreEqual(list[1], 2u);
        _____________________checkMemory();
    }

    TEST_METHOD(List_removeAll_initializer) {
        List<uint32_t> list = { 1, 2, 3,4,5,6,7,8 };
        list.removeAll({ 2,4,1 });

        Assert::AreEqual(list.Size, (size_t)5);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);

        List<uint32_t> testList = { 3,5,6,7,8 };
        size_t i = 0;
        for (auto& item : list)
            Assert::AreEqual(item, testList[i++]);
        _____________________checkMemory();
    }
    TEST_METHOD(List_iterator) {
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
        _____________________checkMemory();
    }

    TEST_METHOD(List_indexOf) {
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
        _____________________checkMemory();
    }

    TEST_METHOD(List_contains) {
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
        _____________________checkMemory();
    }

    TEST_METHOD(List_comparison) {
        List<uint32_t> list = { 1, 2, 3 };
        List<uint32_t> list2 = { 1, 2, 3 };

        Assert::AreEqual(list.Size, (size_t)3);
        Assert::AreEqual(list.Capacity >= list.Size, true);
        Assert::AreEqual(list.Empty, false);
        Assert::IsTrue(list == list2);
        _____________________checkMemory();
    }

    TEST_METHOD(List_performance) {
        Timer timer;
        timer.tick();
        List<uint32_t> list;
        for (size_t i = 0; i < 100000; i++)
            list.add(i);
        timer.tick();
        auto timeList = timer.FrameTimeMs;
        timer.tick();
        std::vector<uint32_t> vector;
        for (size_t i = 0; i < 100000; i++)
            vector.push_back(i);
        timer.tick();
        auto timeVector = timer.FrameTimeMs;
        Assert::IsTrue(timeList < timeVector);
    }
    };
}
