#include "pch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "core/collection/List.h"
#include "core/collection/Tree.h"
#include "core/collection/Set.h"
#include "core/collection/Map.h"
#include "TestAllocator.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;
	using namespace std;

	struct TreeTestValue {
		char c;

		inline bool operator==(const TreeTestValue& other) const {
			return c == other.c;
		}
	};

	TEST_CLASS(TreeTest) {
	public:

		TEST_METHOD(Tree_constructor) {
			MemoryGuard guard;
			{
				Tree<MapTraits<uint32_t, TreeTestValue>> tree;

				Assert::AreEqual(tree.Size, (size_t)0);
				Assert::AreEqual(tree.Empty, true);
#ifdef _DEBUG
				Assert::IsTrue(tree.verify());
#endif
			}
		}

		TEST_METHOD(Tree_constructorCopy) {
			MemoryGuard guard;
			{
				Tree<MapTraits<uint32_t, TreeTestValue>> testTree = { {1, {}}, {2, {}}, {3, {}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = Tree<MapTraits<uint32_t, TreeTestValue>>(testTree);

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
				Tree<MapTraits<uint32_t, TreeTestValue>> testTree = { {1, {}}, {2, {}}, {3, {}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = std::move(testTree);

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
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = { {1, {}}, {2, {}}, {3, {}} };

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
				Tree<MapTraits<uint32_t, TreeTestValue>> testTree = { {1, {}}, {2, {}}, {3, {}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree;
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
				Tree<MapTraits<uint32_t, TreeTestValue>> testTree = { {1, {}}, {2, {}}, {3, {}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree;
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
				Tree<MapTraits<uint32_t, TreeTestValue>> tree;
				tree = { {1, {}}, {2, {}}, {3, {}} };

				Assert::AreEqual(tree.Size, (size_t)3);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1u));
				Assert::IsTrue(tree.contains(2u));
				Assert::IsTrue(tree.contains(3u));
			}
		}

		TEST_METHOD(Tree_put) {
			MemoryGuard guard;
			{
				Tree<SetTraits<uint32_t>> tree;
				tree.put(1);

				Assert::AreEqual(tree.Size, (size_t)1);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1u));
#ifdef _DEBUG
				Assert::IsTrue(tree.verify());
#endif
			}
		}

		TEST_METHOD(Tree_put_operator) {
			MemoryGuard guard;
			{
				Tree<MapTraits<uint32_t, TreeTestValue>> tree;
				tree[1] = {'a'};

				Assert::AreEqual(tree.Size, (size_t)1);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1u));
				Assert::AreEqual(tree.get(1u).c, 'a');
#ifdef _DEBUG
				Assert::IsTrue(tree.verify());
#endif
			}
		}

		TEST_METHOD(Tree_put_duplicates) {
			MemoryGuard guard;
			{
				Tree<SetTraits<uint32_t>> tree;
				tree.put(1);
				tree.put(1);
				tree.put(1);

				Assert::AreEqual(tree.Size, (size_t)1);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1u));
#ifdef _DEBUG
				Assert::IsTrue(tree.verify());
#endif
			}
		}

		TEST_METHOD(Tree_putAll_List) {
			MemoryGuard guard;
			{
				Tree<SetTraits<uint32_t>> tree;
				const List<uint32_t> testList = { 1, 2, 3 };
				tree.putAll(testList);

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
#ifdef _DEBUG
				Assert::IsTrue(tree.verify());
#endif
			}
		}

		TEST_METHOD(Tree_putAll_initializer) {
			MemoryGuard guard;
			{
				Tree<SetTraits<uint32_t>> tree;
				const std::initializer_list<uint32_t> testList = { 1, 2, 3 };
				tree.putAll(testList);

				Assert::AreEqual(tree.Size, (size_t)3);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1u));
				Assert::IsTrue(tree.contains(2u));
				Assert::IsTrue(tree.contains(3u));
#ifdef _DEBUG
				Assert::IsTrue(tree.verify());
#endif
			}
		}

		TEST_METHOD(Tree_putAll_initializerWithDuplicates) {
			MemoryGuard guard;
			{
				Tree<SetTraits<uint32_t>> tree;
				const std::initializer_list<uint32_t> testList = { 1, 2, 3, 3 };
				tree.putAll(testList);

				Assert::AreEqual(tree.Size, (size_t)3);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1u));
				Assert::IsTrue(tree.contains(2u));
				Assert::IsTrue(tree.contains(3u));
#ifdef _DEBUG
				Assert::IsTrue(tree.verify());
#endif
			}
		}

		TEST_METHOD(Tree_remove) {
			MemoryGuard guard;
			{
				Tree<SetTraits<uint32_t>> tree = { 1, 2, 3, 5, 20, 4, 7, 14, 22, 6 };
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
				Tree<SetTraits<uint32_t>> tree = { 4, 7, 14, 22, 6 ,1, 2, 3, 5, 20, 12, 13, 53, 42, 76, 8, 9, 0 };
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
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = { {1, {}}, {2, {}} };
				tree.remove(2);

				Assert::AreEqual(tree.Size, (size_t)1);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1u));
				Assert::IsFalse(tree.contains(2u));
				Assert::IsTrue(tree.verify());
			}
			{
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = { {1, {}} };
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
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = { {1, {}}, {2, {}}, {3, {}} };
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
				Tree<SetTraits<uint32_t>> tree = { 1, 2, 3 };

				Assert::AreEqual(tree.Size, (size_t)3);
				Assert::AreEqual(tree.Empty, false);

				size_t i = 0;
				for (auto& item : tree)
					Assert::AreEqual(item, testVector[i++]);
			}

			{
				std::vector<uint32_t> testVector = { 1, 2, 3 };
				const Tree<SetTraits<uint32_t>> tree = { 1, 2, 3 };

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
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = { {1, {}}, {2, {}}, {3, {}} };

				Assert::AreEqual(tree.Size, (size_t)3);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1));
				Assert::IsFalse(tree.contains(4));
			}

			{
				const Tree<MapTraits<uint32_t, TreeTestValue>> tree = { {1, {}}, {2, {}}, {3, {}} };

				Assert::AreEqual(tree.Size, (size_t)3);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree.contains(1));
				Assert::IsFalse(tree.contains(4));
			}
		}

		TEST_METHOD(Tree_comparison) {
			MemoryGuard guard;
			{
				Tree<MapTraits<uint32_t, TreeTestValue>> tree = { {1, {'a'}}, {2, {'b'}}, {3, {'c'}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree2 = { {1, {'a'}}, {2, {'b'}}, {3, {'c'}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree3 = { {1, {'d'}}, {2, {'b'}}, {3, {'c'}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree4 = { {1, {'a'}}, {2, {'b'}}, {3, {'c'}}, {4, {'d'}} };
				Tree<MapTraits<uint32_t, TreeTestValue>> tree5 = { {1, {'d'}}, {4, {'b'}}, {3, {'c'}} };

				Assert::AreEqual(tree.Size, (size_t)3);
				Assert::AreEqual(tree.Empty, false);
				Assert::IsTrue(tree == tree2);
				Assert::IsFalse(tree != tree2);
				Assert::IsFalse(tree == tree3);
				Assert::IsTrue(tree != tree3);
				Assert::IsFalse(tree == tree4);
				Assert::IsTrue(tree != tree4);
				Assert::IsFalse(tree == tree5);
				Assert::IsTrue(tree != tree5);
			}
		}
	};
}
