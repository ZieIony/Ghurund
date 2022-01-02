#include "pch.h"
#include "CppUnitTest.h"
#include "MemoryGuard.h"

#include "core/collection/List.h"
#include "core/collection/Tree.h"
#include "TestAllocator.h"

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

    TEST_CLASS(TreeTest) {
public:

    TEST_METHOD(Tree_constructor) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree;

            Assert::AreEqual(tree.Size, (size_t)0);
            Assert::AreEqual(tree.Empty, true);
            Assert::IsTrue(tree.verify());
        }

        {
            Tree<TestClass> tree;

            Assert::AreEqual(tree.Size, (size_t)0);
            Assert::AreEqual(tree.Empty, true);
            Assert::IsTrue(tree.verify());
        }
    }
    
    TEST_METHOD(Tree_constructorCopy) {
        MemoryGuard guard;
        {
            Tree<uint32_t> testTree = { 1, 2, 3 };
            Tree<uint32_t> tree = Tree<uint32_t>(testTree);

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
        }
    }

    TEST_METHOD(Tree_constructorMove) {
        MemoryGuard guard;
        {
            Tree<uint32_t> testTree = { 1, 2, 3 };
            Tree<uint32_t> tree = std::move(testTree);

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
        }
    }

    TEST_METHOD(Tree_constructorInitializer) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree = { 1, 2, 3 };

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
        }
    }

    TEST_METHOD(Tree_referenceAssignment) {
        MemoryGuard guard;
        {
            Tree<uint32_t> testTree = { 1, 2, 3 };
            Tree<uint32_t> tree;
            tree = testTree;

            Assert::AreEqual(tree.Size, testTree.Size);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
        }
    }

    TEST_METHOD(Tree_moveAssignment) {
        MemoryGuard guard;
        {
            Tree<uint32_t> testTree = { 1, 2, 3 };
            Tree<uint32_t> tree;
            tree = std::move(testTree);

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
        }
    }

    TEST_METHOD(Tree_initializerAssignment) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree;
            tree = { 1, 2, 3 };

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
        }
    }

    TEST_METHOD(Tree_add) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree;
            tree.add(1);

            Assert::AreEqual(tree.Size, (size_t)1);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.verify());
        }
    }

    TEST_METHOD(Tree_addAllInitializer) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree;
            tree.addAll({ 1, 2, 3, 5, 20, 4, 7, 14, 22, 6 });

            Assert::AreEqual(tree.Size, (size_t)10);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(20u));
            Assert::IsTrue(tree.contains(6u));
            Assert::IsTrue(tree.verify());
        }
    }

    TEST_METHOD(Tree_addAll_List) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree;
            const List<uint32_t> testList = { 1, 2, 3 };
            tree.addAll(testList);

            Assert::AreEqual(testList.Size, (size_t)3);
            Assert::AreEqual(testList.Empty, false);
            Assert::IsTrue(testList.contains(1u));
            Assert::IsTrue(testList.contains(2u));
            Assert::IsTrue(testList.contains(3u));

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
            Assert::IsTrue(tree.verify());
        }
    }

    TEST_METHOD(Tree_addAll_initializer) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree;
            const std::initializer_list<uint32_t> testList = { 1, 2, 3 };
            tree.addAll(testList);

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
            Assert::IsTrue(tree.verify());
        }
    }

    TEST_METHOD(Tree_addAll_initializerWithDuplicates) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree;
            const std::initializer_list<uint32_t> testList = { 1, 2, 3, 3 };
            tree.addAll(testList);

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
            Assert::IsTrue(tree.verify());
        }
    }

    TEST_METHOD(Tree_remove) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree = { 1, 2, 3, 5, 20, 4, 7, 14, 22, 6 };
            tree.remove(2);
            Assert::IsTrue(tree.verify());
            tree.remove(20);
            Assert::IsTrue(tree.verify());
            tree.remove(7);
            Assert::IsTrue(tree.verify());
            tree.remove(22);
            Assert::IsTrue(tree.verify());
            tree.remove(1);
            Assert::IsTrue(tree.verify());
            tree.remove(3);
            Assert::IsTrue(tree.verify());
            tree.remove(5);
            Assert::IsTrue(tree.verify());
            tree.remove(14);
            Assert::IsTrue(tree.verify());
            tree.remove(6);
            Assert::IsTrue(tree.verify());
            tree.remove(4);

            Assert::AreEqual(tree.Size, (size_t)0);
            Assert::AreEqual(tree.Empty, true);
            Assert::IsFalse(tree.contains(1u));
            Assert::IsFalse(tree.contains(2u));
            Assert::IsFalse(tree.contains(3u));
            Assert::IsTrue(tree.verify());
        }
        {
            Tree<uint32_t> tree = { 4, 7, 14, 22, 6 ,1, 2, 3, 5, 20, 12, 13, 53, 42, 76, 8, 9, 0 };
            tree.remove(2);
            Assert::IsTrue(tree.verify());
            tree.remove(20);
            Assert::IsTrue(tree.verify());
            tree.remove(7);
            Assert::IsTrue(tree.verify());
            tree.remove(22);
            Assert::IsTrue(tree.verify());
            tree.remove(1);
            Assert::IsTrue(tree.verify());
            tree.remove(3);
            Assert::IsTrue(tree.verify());
            tree.remove(5);
            Assert::IsTrue(tree.verify());
            tree.remove(14);
            Assert::IsTrue(tree.verify());
            tree.remove(6);
            Assert::IsTrue(tree.verify());
            tree.remove(4);

            Assert::AreEqual(tree.Size, (size_t)8);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(12u));
            Assert::IsTrue(tree.contains(76u));
            Assert::IsTrue(tree.contains(9u));
            Assert::IsTrue(tree.verify());
        }
        {
            Tree<uint32_t> tree = { 1, 2 };
            tree.remove(2);

            Assert::AreEqual(tree.Size, (size_t)1);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsFalse(tree.contains(2u));
            Assert::IsTrue(tree.verify());
        }
        {
            Tree<uint32_t> tree = { 1 };
            tree.remove(1);

            Assert::AreEqual(tree.Size, (size_t)0);
            Assert::AreEqual(tree.Empty, true);
            Assert::IsFalse(tree.contains(1u));
            Assert::IsTrue(tree.verify());
        }
    }

    TEST_METHOD(Tree_removeNonexisting) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree = { 1, 2, 3 };
            tree.remove(4);

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1u));
            Assert::IsTrue(tree.contains(2u));
            Assert::IsTrue(tree.contains(3u));
            Assert::IsFalse(tree.contains(4u));
            Assert::IsTrue(tree.verify());
        }
    }

    TEST_METHOD(Tree_iterator) {
        MemoryGuard guard;
        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            Tree<uint32_t> tree = { 1, 2, 3 };

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);

            size_t i = 0;
            for (auto& item : tree)
                Assert::AreEqual(item, testVector[i++]);
        }

        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            const Tree<uint32_t> tree = { 1, 2, 3 };

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);

            size_t i = 0;
            for (auto& item : tree)
                Assert::AreEqual(item, testVector[i++]);
        }
    }

    TEST_METHOD(Tree_contains) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree = { 1, 2, 3 };

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1));
            Assert::IsFalse(tree.contains(4));
        }

        {
            const Tree<uint32_t> tree = { 1, 2, 3 };

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree.contains(1));
            Assert::IsFalse(tree.contains(4));
        }
    }

    TEST_METHOD(Tree_comparison) {
        MemoryGuard guard;
        {
            Tree<uint32_t> tree = { 1, 2, 3 };
            Tree<uint32_t> tree2 = { 1, 2, 3 };

            Assert::AreEqual(tree.Size, (size_t)3);
            Assert::AreEqual(tree.Empty, false);
            Assert::IsTrue(tree == tree2);
        }
    }
    };
}
