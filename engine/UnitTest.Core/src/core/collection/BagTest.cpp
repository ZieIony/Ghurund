#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/Bag.h"
#include "core/collection/Stack.h"
#include "TestUtils.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;
    using namespace std;

    struct TestClass {
        uint32_t val = 5;
        const char* text = "text";
    };

    TEST_CLASS(BagTest) {
public:

    TEST_METHOD(Bag_constructor) {
        {
            Bag<uint32_t> bag;

            Assert::AreEqual(bag.Size, (size_t)0);
            Assert::AreEqual(bag.Capacity >= bag.Size, true);
            Assert::AreEqual(bag.Empty, true);
        }
        _____________________checkMemory();

        {
            Bag<TestClass> bag;

            Assert::AreEqual(bag.Size, (size_t)0);
            Assert::AreEqual(bag.Capacity >= bag.Size, true);
            Assert::AreEqual(bag.Empty, true);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_constructor_initial) {
        {
            Bag<uint32_t> bag(20);

            Assert::AreEqual(bag.Size, (size_t)0);
            Assert::AreEqual(bag.Capacity, (size_t)20);
            Assert::AreEqual(bag.Empty, true);
        }
        _____________________checkMemory();

        {
            Bag<TestClass> bag(20);

            Assert::AreEqual(bag.Size, (size_t)0);
            Assert::AreEqual(bag.Capacity, (size_t)20);
            Assert::AreEqual(bag.Empty, true);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_constructor_copy) {
        Bag<uint32_t> testBag = { 1, 2, 3 };
        Bag<uint32_t> bag = Bag<uint32_t>(testBag);

        Assert::AreEqual(bag.Size, (size_t)3);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_constructor_move) {
        Bag<uint32_t> testBag = { 1, 2, 3 };
        Bag<uint32_t> bag = std::move(testBag);

        Assert::AreEqual(bag.Size, (size_t)3);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_constructor_initializer) {
        Bag<uint32_t> bag = { 1, 2, 3 };

        Assert::AreEqual(bag.Size, (size_t)3);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_constructor_initializerWithDuplicates) {
        Bag<uint32_t> bag = { 1, 2, 3, 2, 1 };

        Assert::AreEqual(bag.Size, (size_t)5);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_referenceAssignment) {
        Stack<uint32_t> testStack = { 1, 2, 3 };
        Bag<uint32_t> bag;
        bag = testStack;

        Assert::AreEqual(bag.Size, testStack.Size);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_setReferenceAssignment) {
        Bag<uint32_t> testBag = { 1, 2, 3 };
        Bag<uint32_t> bag;
        bag = testBag;

        Assert::AreEqual(bag.Size, testBag.Size);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_moveAssignment) {
        Bag<uint32_t> testBag = { 1, 2, 3 };
        Bag<uint32_t> bag;
        bag = std::move(testBag);

        Assert::AreEqual(bag.Size, (size_t)3);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_initializerAssignment) {
        {
            Bag<uint32_t> bag;
            bag = { 1, 2, 3 };

            Assert::AreEqual(bag.Size, (size_t)3);
            Assert::AreEqual(bag.Capacity >= bag.Size, true);
            Assert::AreEqual(bag.Empty, false);
            Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        }
        _____________________checkMemory();
    }

    TEST_METHOD(TestBagAdd) {
        Bag<uint32_t> bag;
        bag.add(1);

        Assert::AreEqual(bag.Size, (size_t)1);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1 }));
        _____________________checkMemory();
    }

    TEST_METHOD(TestBagAddAllInitializer) {
        Bag<uint32_t> bag;
        bag.addAll({ 1, 2, 3 });

        Assert::AreEqual(bag.Size, (size_t)3);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_addAll_Bag) {
        Bag<uint32_t> bag;
        const Bag<uint32_t> testBag = { 1, 2, 3 };
        bag.addAll(testBag);

        Assert::AreEqual(testBag.Size, (size_t)3);
        Assert::AreEqual(testBag.Capacity >= bag.Size, true);
        Assert::AreEqual(testBag.Empty, false);
        Assert::IsTrue(collectionContains(testBag, { 1, 2, 3 }));

        Assert::AreEqual(bag.Size, (size_t)3);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));

        Assert::AreEqual(bag.Size, testBag.Size);
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_addAll_ListDuplicates) {
        Bag<uint32_t> bag;
        const List<uint32_t> testList = { 1, 2, 3, 2, 1 };
        bag.addAll(testList);

        Assert::AreEqual(testList.Size, (size_t)5);
        Assert::AreEqual(testList.Capacity >= bag.Size, true);
        Assert::AreEqual(testList.Empty, false);
        Assert::IsTrue(collectionContains(testList, { 1, 2, 3 }));

        Assert::AreEqual(bag.Size, (size_t)5);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 2, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_remove) {
        Bag<uint32_t> bag = { 1, 2, 3 };
        bag.remove(2);

        Assert::AreEqual(bag.Size, (size_t)2);
        Assert::AreEqual(bag.Capacity >= bag.Size, true);
        Assert::AreEqual(bag.Empty, false);
        Assert::IsTrue(collectionContains(bag, { 1, 3 }));
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_iterator) {
        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            Bag<uint32_t> bag = { 1, 2, 3 };

            Assert::AreEqual(bag.Size, (size_t)3);
            Assert::AreEqual(bag.Capacity >= bag.Size, true);
            Assert::AreEqual(bag.Empty, false);
            Assert::IsTrue(collectionContains(bag, testVector));
        }

        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            const Bag<uint32_t> bag = { 1, 2, 3 };

            Assert::AreEqual(bag.Size, (size_t)3);
            Assert::AreEqual(bag.Capacity >= bag.Size, true);
            Assert::AreEqual(bag.Empty, false);
            Assert::IsTrue(collectionContains(bag, testVector));
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_contains) {
        {
            Bag<uint32_t> bag = { 1, 2, 3 };

            Assert::IsTrue(bag.contains(1));
            Assert::IsFalse(bag.contains(4));
        }

        {
            const Bag<uint32_t> bag = { 1, 2, 3 };

            Assert::IsTrue(bag.contains(1));
            Assert::IsFalse(bag.contains(4));
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Bag_comparison) {
        Bag<uint32_t> bag = { 1, 2, 3 };
        Bag<uint32_t> bag2 = { 1, 2, 3 };

        Assert::IsTrue(bag == bag2);
        _____________________checkMemory();
    }
    };
}
