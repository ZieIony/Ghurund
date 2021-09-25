#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/Set.h"
#include "core/collection/Stack.h"

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

    TEST_CLASS(SetTest) {
public:

    TEST_METHOD(Set_constructor) {
        {
            Set<uint32_t> set;

            Assert::AreEqual(set.Size, (size_t)0);
            Assert::AreEqual(set.Capacity >= set.Size, true);
            Assert::AreEqual(set.Empty, true);
        }
        _____________________checkMemory();

        {
            Set<TestClass> set;

            Assert::AreEqual(set.Size, (size_t)0);
            Assert::AreEqual(set.Capacity >= set.Size, true);
            Assert::AreEqual(set.Empty, true);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Set_constructorInitial) {
        {
            Set<uint32_t> set(20);

            Assert::AreEqual(set.Size, (size_t)0);
            Assert::AreEqual(set.Capacity, (size_t)20);
            Assert::AreEqual(set.Empty, true);
        }
        _____________________checkMemory();

        {
            Set<TestClass> set(20);

            Assert::AreEqual(set.Size, (size_t)0);
            Assert::AreEqual(set.Capacity, (size_t)20);
            Assert::AreEqual(set.Empty, true);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Set_constructorCopy) {
        Set<uint32_t> testSet = { 1, 2, 3 };
        Set<uint32_t> set = Set<uint32_t>(testSet);

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_constructorMove) {
        Set<uint32_t> testSet = { 1, 2, 3 };
        Set<uint32_t> set = std::move(testSet);

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_constructor_initializer) {
        Set<uint32_t> set = { 1, 2, 3 };

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_constructor_initializerWithDuplicates) {
        Set<uint32_t> set = { 1, 2, 3, 2, 1 };

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_referenceAssignment) {
        Stack<uint32_t> testStack = { 1, 2, 3 };
        Set<uint32_t> set;
        set = testStack;

        Assert::AreEqual(set.Size, testStack.Size);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_setReferenceAssignment) {
        Set<uint32_t> testSet = { 1, 2, 3 };
        Set<uint32_t> set;
        set = testSet;

        Assert::AreEqual(set.Size, testSet.Size);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_moveAssignment) {
        Set<uint32_t> testSet = { 1, 2, 3 };
        Set<uint32_t> set;
        set = std::move(testSet);

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_initializerAssignment) {
        {
            Set<uint32_t> set;
            set = { 1, 2, 3 };

            Assert::AreEqual(set.Size, (size_t)3);
            Assert::AreEqual(set.Capacity >= set.Size, true);
            Assert::AreEqual(set.Empty, false);
            for (auto val : { 1, 2, 3 })
                Assert::IsTrue(set.contains(val));
        }
        _____________________checkMemory();
    }

    TEST_METHOD(TestSetAdd) {
        Set<uint32_t> set;
        set.add(1);

        Assert::AreEqual(set.Size, (size_t)1);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(TestSetAddAllInitializer) {
        Set<uint32_t> set;
        set.addAll({ 1, 2, 3 });

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_addAll_Set) {
        Set<uint32_t> set;
        const Set<uint32_t> testSet = { 1, 2, 3 };
        set.addAll(testSet);

        Assert::AreEqual(testSet.Size, (size_t)3);
        Assert::AreEqual(testSet.Capacity >= set.Size, true);
        Assert::AreEqual(testSet.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));

        Assert::AreEqual(set.Size, testSet.Size);
        _____________________checkMemory();
    }

    TEST_METHOD(Set_addAll_ListDuplicates) {
        Set<uint32_t> set;
        const List<uint32_t> testList = { 1, 2, 3, 2, 1 };
        set.addAll(testList);

        Assert::AreEqual(testList.Size, (size_t)5);
        Assert::AreEqual(testList.Capacity >= set.Size, true);
        Assert::AreEqual(testList.Empty, false);
        for (auto val : { 1, 2, 3, 2, 1 })
            Assert::IsTrue(testList.contains(val));

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 2, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_remove) {
        Set<uint32_t> set = { 1, 2, 3 };
        set.remove(2);

        Assert::AreEqual(set.Size, (size_t)2);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        for (auto val : { 1, 3 })
            Assert::IsTrue(set.contains(val));
        _____________________checkMemory();
    }

    TEST_METHOD(Set_iterator) {
        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            Set<uint32_t> set = { 1, 2, 3 };

            Assert::AreEqual(set.Size, (size_t)3);
            Assert::AreEqual(set.Capacity >= set.Size, true);
            Assert::AreEqual(set.Empty, false);

            size_t i = 0;
            for (auto& item : set)
                Assert::AreEqual(item, testVector[i++]);
        }

        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            const Set<uint32_t> set = { 1, 2, 3 };

            Assert::AreEqual(set.Size, (size_t)3);
            Assert::AreEqual(set.Capacity >= set.Size, true);
            Assert::AreEqual(set.Empty, false);

            size_t i = 0;
            for (auto& item : set)
                Assert::AreEqual(item, testVector[i++]);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Set_contains) {
        {
            Set<uint32_t> set = { 1, 2, 3 };

            Assert::AreEqual(set.Size, (size_t)3);
            Assert::AreEqual(set.Capacity >= set.Size, true);
            Assert::AreEqual(set.Empty, false);
            Assert::IsTrue(set.contains(1));
            Assert::IsFalse(set.contains(4));
        }

        {
            const Set<uint32_t> set = { 1, 2, 3 };

            Assert::AreEqual(set.Size, (size_t)3);
            Assert::AreEqual(set.Capacity >= set.Size, true);
            Assert::AreEqual(set.Empty, false);
            Assert::IsTrue(set.contains(1));
            Assert::IsFalse(set.contains(4));
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Set_comparison) {
        Set<uint32_t> set = { 1, 2, 3 };
        Set<uint32_t> set2 = { 1, 2, 3 };

        Assert::AreEqual(set.Size, (size_t)3);
        Assert::AreEqual(set.Capacity >= set.Size, true);
        Assert::AreEqual(set.Empty, false);
        Assert::IsTrue(set == set2);
        _____________________checkMemory();
    }
    };
}
