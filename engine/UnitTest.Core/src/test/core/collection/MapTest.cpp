#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/string/String.h"
#include "TestAllocator.h"
#include "test/MemoryGuard.h"
#include "test/TestUtils.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;
	using namespace std;

	struct CustomTraitsTestClass {
		int a;

		CustomTraitsTestClass(int a):a(a) {}
	};

	struct CustomMapTraits {
		using key_t = uint32_t;
		using value_t = CustomTraitsTestClass;
		using data_t = KeyValuePair<uint32_t, CustomTraitsTestClass>;

		int defaultValue = 5;

		inline const key_t& getKey(const data_t& data) const {
			return data.key;
		}

		inline data_t makeData(const key_t& key) const {
			return { key, { defaultValue } };
		}

		inline data_t makeData(const key_t& key, const value_t& value) const {
			return { key, value };
		}
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
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
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
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
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
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
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

				Assert::AreEqual(map.Size, testMap.Size);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
				Assert::IsTrue(map.containsValue("a"));
				Assert::IsTrue(map.containsValue("b"));
				Assert::IsTrue(map.containsValue("c"));
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
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
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
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
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
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
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
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
				Assert::IsTrue(map.containsValue("a"));
				Assert::IsTrue(map.containsValue("b"));
				Assert::IsTrue(map.containsValue("c"));
			}
		}

		TEST_METHOD(Map_moveAssignment_differentAllocators) {
			MemoryGuard guard;
			{
				TestAllocator allocator1;
				Map<uint32_t, uint32_t, TestAllocator> testMap(allocator1);
				TestAllocator allocator2;
				Map<uint32_t, uint32_t, TestAllocator> map(allocator2);
				auto func = [&] { map = std::move(testMap); };
				Assert::ExpectException<IncompatibleAllocatorsException>(func);
			}
		}

		TEST_METHOD(Map_put) {
			MemoryGuard guard;
			{
				Map<uint32_t, AString> map;
				map.put(1, "a");

				Assert::AreEqual(map.Size, (size_t)1);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.containsValue("a"));
			}
		}

		TEST_METHOD(Map_put_operator) {
			MemoryGuard guard;
			{
				Map<uint32_t, AString> map;
				map[1] = "test";

				Assert::AreEqual(map.Size, (size_t)1);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::AreEqual(map.get(1u), AString("test"));
#ifdef _DEBUG
				Assert::IsTrue(map.verify());
#endif
			}
		}

		TEST_METHOD(Map_put_duplicates) {
			MemoryGuard guard;
			{
				Map<uint32_t, AString> map;
				map.put(1, "a");
				map.put(1, "b");
				map.put(1, "c");

				Assert::AreEqual(map.Size, (size_t)1);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::AreEqual(map.get(1), AString("c"));
#ifdef _DEBUG
				Assert::IsTrue(map.verify());
#endif
			}
		}

		TEST_METHOD(Map_putAll_List) {
			MemoryGuard guard;
			{
				Map<uint32_t, AString> map;
				KeyValuePair<uint32_t, AString> a = { 1, "a" }, b = { 2, "b" }, c = { 3, "c" };
				const List<KeyValuePair<uint32_t, AString>> testList = { a, b, c };
				map.putAll(testList);

				Assert::AreEqual(testList.Size, (size_t)3);
				Assert::AreEqual(testList.Empty, false);
				Assert::IsTrue(testList.contains(a));
				Assert::IsTrue(testList.contains(b));
				Assert::IsTrue(testList.contains(c));

				Assert::AreEqual(map.Size, (size_t)3);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
#ifdef _DEBUG
				Assert::IsTrue(map.verify());
#endif
			}
		}

		TEST_METHOD(Map_putAll_initializer) {
			MemoryGuard guard;
			{
				Map<uint32_t, AString> map;
				const std::initializer_list<KeyValuePair<uint32_t, AString>> testList = { {1, "a"}, {2, "a"}, {3, "a"} };
				map.putAll(testList);

				Assert::AreEqual(map.Size, (size_t)3);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
#ifdef _DEBUG
				Assert::IsTrue(map.verify());
#endif
			}
		}

		TEST_METHOD(Map_putAll_initializerWithDuplicates) {
			MemoryGuard guard;
			{
				Map<uint32_t, AString> map;
				const std::initializer_list<KeyValuePair<uint32_t, AString>> testList = { {1, "a"}, {2, "a"}, {3, "a"}, {3, "a"} };
				map.putAll(testList);

				Assert::AreEqual(map.Size, (size_t)3);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
#ifdef _DEBUG
				Assert::IsTrue(map.verify());
#endif
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
				Assert::IsFalse(map.contains(1u));
				Assert::IsFalse(map.contains(2u));
				Assert::IsFalse(map.contains(3u));
			}
			{
				Map<uint32_t, AString> map = { {1, "a"}, {2, "b"} };
				map.remove(2);

				Assert::AreEqual(map.Size, (size_t)1);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::IsFalse(map.contains(2u));
			}
			{
				Map<uint32_t, AString> map = { {1, "a"} };
				map.remove(1);

				Assert::AreEqual(map.Size, (size_t)0);
				Assert::AreEqual(map.Empty, true);
				Assert::IsFalse(map.contains(1u));
			}
		}

		TEST_METHOD(Map_removeNonexisting) {
			MemoryGuard guard;
			{
				Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };
				map.remove(4);

				Assert::AreEqual(map.Size, (size_t)3);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1u));
				Assert::IsTrue(map.contains(2u));
				Assert::IsTrue(map.contains(3u));
				Assert::IsFalse(map.contains(4u));
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
				Assert::IsTrue(map.contains(1));
				Assert::IsTrue(map.containsValue("a"));
				Assert::IsFalse(map.contains(4));
				Assert::IsFalse(map.containsValue("d"));
			}

			{
				const Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };

				Assert::AreEqual(map.Size, (size_t)3);
				Assert::AreEqual(map.Empty, false);
				Assert::IsTrue(map.contains(1));
				Assert::IsTrue(map.containsValue("a"));
				Assert::IsFalse(map.contains(4));
				Assert::IsFalse(map.containsValue("d"));
			}
		}

		TEST_METHOD(Map_comparison) {
			Map<uint32_t, AString> map = { {1, "a"}, {2, "b"}, {3, "c"} };
			Map<uint32_t, AString> map2 = { {1, "a"}, {2, "b"}, {3, "c"} };

			Assert::AreEqual(map.Size, (size_t)3);
			Assert::AreEqual(map.Empty, false);
			Assert::IsTrue(map == map2);
			_____________________checkMemory();
		}

		TEST_METHOD(Map_customTraits) {
			Map<uint32_t, CustomTraitsTestClass, SimpleAllocator, CustomMapTraits> map;

			map[1];
			map[2] = CustomTraitsTestClass(4);

			Assert::AreEqual(map.Size, (size_t)2);
			Assert::AreEqual(map.Empty, false);
			Assert::AreEqual(5, map.get(1).a);
			Assert::AreEqual(4, map.get(2).a);
			_____________________checkMemory();
		}
	};
}
