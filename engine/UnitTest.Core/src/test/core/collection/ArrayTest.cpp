#include "utcpch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "core/collection/Array.h"
#include "core/collection/Stack.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;
	using namespace std;

	TEST_CLASS(ArrayTest) {
public:

	TEST_METHOD(Array_constructor) {
		MemoryGuard guard;
		{
			Array<TestClass> array;

			Assert::AreEqual((size_t)0, array.Size);
			Assert::AreEqual(true, array.Empty);
		}
	}

	TEST_METHOD(Array_constructorInitial) {
		MemoryGuard guard;
		{
			Array<uint32_t> array(20);

			Assert::AreEqual((size_t)20, array.Size);
			Assert::AreEqual(false, array.Empty);
		}

		{
			Array<TestClass> array(20);

			Assert::AreEqual((size_t)20, array.Size);
			Assert::AreEqual(false, array.Empty);
		}
	}

	TEST_METHOD(Array_constructorCopy) {
		MemoryGuard guard;
		{
			Array<uint32_t> testArray = { 1, 2, 3 };
			Array<uint32_t> array = Array<uint32_t>(testArray);

			Assert::AreEqual((size_t)3ull, array.Size);
			Assert::AreEqual(false, array.Empty);
			Assert::AreEqual(1u, array[0]);
			Assert::AreEqual(2u, array[1]);
			Assert::AreEqual(3u, array[2]);
		}
	}

	TEST_METHOD(Array_constructorMove) {
		MemoryGuard guard;
		{
			Array<uint32_t> testArray = { 1, 2, 3 };
			Array<uint32_t> array = std::move(testArray);

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 2u);
			Assert::AreEqual(array[2], 3u);
		}
	}

	TEST_METHOD(Array_constructorInitializer) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 2u);
			Assert::AreEqual(array[2], 3u);
		}
	}

	TEST_METHOD(Array_arrayReferenceAssignment) {
		MemoryGuard guard;
		{
			Array<uint32_t> testArray = { 1, 2, 3 };
			Array<uint32_t> array;
			Array<uint32_t> a = array = testArray;

			Assert::AreEqual(array.Size, testArray.Size);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 2u);
			Assert::AreEqual(array[2], 3u);
		}
	}

	TEST_METHOD(Array_moveAssignment) {
		MemoryGuard guard;
		{
			Array<uint32_t> testArray = { 1, 2, 3 };
			Array<uint32_t> array;
			array = std::move(testArray);

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 2u);
			Assert::AreEqual(array[2], 3u);
		}
	}

	TEST_METHOD(Array_initializerAssignment) {
		MemoryGuard guard;
		{
			Array<uint32_t> array;
			array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 2u);
			Assert::AreEqual(array[2], 3u);
		}
	}

	TEST_METHOD(Array_set) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3 };
			array.set(1, 4);

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 4u);
			Assert::AreEqual(array[2], 3u);
		}
	}

	TEST_METHOD(Array_get) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3 };
			auto val = array.get(1);

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 2u);
			Assert::AreEqual(array[2], 3u);
			Assert::AreEqual(val, 2u);
		}

		{
			Array<uint32_t> array2 = { 1, 2, 3 };
			const uint32_t& val2 = array2.get(1);
		}
	}

	TEST_METHOD(Array_arrayOperator) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3 };
			uint32_t& val = array[1];

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array[0], 1u);
			Assert::AreEqual(array[1], 2u);
			Assert::AreEqual(array[2], 3u);
			Assert::AreEqual(val, 2u);

			// does it compile with const?
			const Array<uint32_t> array2 = { 1, 2, 3 };
			const uint32_t& val2 = array2[1];
		}
	}

	TEST_METHOD(Array_subarray) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3, 4, 5, 6 };
			Array<uint32_t> array2 = array.subarray(2, 5);

			Assert::AreEqual((size_t)6, array.Size);
			Assert::AreEqual(false, array.Empty);

			Assert::AreEqual((size_t)3, array2.Size);
			Assert::AreEqual(false, array2.Empty);

			Array<uint32_t> testArray = { 1, 2, 3, 4, 5, 6 };
			size_t i = 0;
			for (auto& item : array)
				Assert::AreEqual(item, testArray[i++]);

			Array<uint32_t> testArray2 = { 3, 4, 5 };
			size_t j = 0;
			for (auto& item : array2)
				Assert::AreEqual(item, testArray2[j++]);
		}
	}

	TEST_METHOD(Array_iterator) {
		MemoryGuard guard;
		{
			std::vector<uint32_t> testVector = { 1, 2, 3 };
			Array<uint32_t> array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);

			size_t i = 0;
			for (auto& item : array)
				Assert::AreEqual(item, testVector[i++]);
		}

		{
			std::vector<uint32_t> testVector = { 1, 2, 3 };
			const Array<uint32_t> array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);

			size_t i = 0;
			for (auto& item : array)
				Assert::AreEqual(item, testVector[i++]);
		}
	}

	TEST_METHOD(Array_indexOf) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array.indexOf(2), (size_t)1);
			Assert::AreEqual(array.indexOf(4), (size_t)3);
		}

		{
			const Array<uint32_t> array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::AreEqual(array.indexOf(2), (size_t)1);
			Assert::AreEqual(array.indexOf(4), (size_t)3);
		}
	}

	TEST_METHOD(Array_contains) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::IsTrue(array.contains(1));
			Assert::IsFalse(array.contains(4));
		}

		{
			const Array<uint32_t> array = { 1, 2, 3 };

			Assert::AreEqual(array.Size, (size_t)3);
			Assert::AreEqual(array.Empty, false);
			Assert::IsTrue(array.contains(1));
			Assert::IsFalse(array.contains(4));
		}
	}

	TEST_METHOD(Array_comparison) {
		MemoryGuard guard;
		{
			Array<uint32_t> array = { 1, 2, 3 };
			Array<uint32_t> array2 = { 1, 2, 3 };
			Array<uint32_t> array3 = { 1, 2, 3, 4 };
			Array<uint32_t> array4 = { 1, 2, 4 };
			Array<uint32_t> array5 = array;

			Assert::IsTrue(array == array2);
			Assert::IsFalse(array != array2);
			Assert::IsFalse(array == array3);
			Assert::IsTrue(array != array3);
			Assert::IsFalse(array == array4);
			Assert::IsTrue(array != array4);
			Assert::IsTrue(array == array5);
			Assert::IsFalse(array != array5);
		}
	}
	};
}
