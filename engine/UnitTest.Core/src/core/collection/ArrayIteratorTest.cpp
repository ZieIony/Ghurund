#include "pch.h"
#include "CppUnitTest.h"
#include "TestUtils.h"
#include "MemoryGuard.h"
#include "TestClass.h"

#include "core/collection/iterator/ArrayIterator.h"

#include <iostream>
#include <vector>
#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;
    using namespace std;

    // https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
    TEST_CLASS(ArrayIteratorTest) {
public:

    TEST_METHOD(ArrayIterator_defaultConstructor) {
        MemoryGuard guard;
        {
            ArrayIterator<uint32_t> it;
        }
    }

    TEST_METHOD(ArrayIterator_constructor) {
        MemoryGuard guard;
        {
            uint32_t v[2] = { 0,1 };
            ArrayIterator<uint32_t> it(&v[0]);
        }
    }

    TEST_METHOD(ArrayIterator_copyConstructor) {
        MemoryGuard guard;
        {
            const ArrayIterator<uint32_t> it;
            ArrayIterator<uint32_t> it2(it);
        }
    }

    TEST_METHOD(ArrayIterator_assignment) {
        MemoryGuard guard;
        {
            ArrayIterator<uint32_t> it;
            const ArrayIterator<uint32_t> it2;
            it = it2;
        }
    }

    TEST_METHOD(ArrayIterator_equality) {
        MemoryGuard guard;
        {
            uint32_t v[2] = { 0,1 };
            ArrayIterator<uint32_t> it(&v[0]);
            ArrayIterator<uint32_t> it2(&v[0]);
            ArrayIterator<uint32_t> it3(&v[1]);

            Assert::IsTrue(it == it2);
            Assert::IsFalse(it == it3);
            Assert::IsFalse(it != it2);
            Assert::IsTrue(it != it3);
        }
    }

    TEST_METHOD(ArrayIterator_dereference) {
        MemoryGuard guard;
        {
            UnitTest::TestClass v[2] = { {},{} };
            ArrayIterator<UnitTest::TestClass> it(&v[0]);
            auto& a = *it;
            auto b = it->val;
        }
        {
            uint32_t v[2] = { 0,1 };
            ArrayIterator<uint32_t> it(&v[0]);
            *it = 3;

            Assert::AreEqual(3u, v[0]);
        }
    }

    TEST_METHOD(ArrayIterator_increment) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ArrayIterator<uint32_t> it(&v[0]);
            ArrayIterator<uint32_t> it2(&v[0]);
            ArrayIterator<uint32_t> it3(&v[0]);
            auto it4 = it++;
            auto& it5 = ++it2;
            auto val = *it3++;

            Assert::AreEqual(it, it2);
            Assert::AreNotEqual(it, it4);
            Assert::AreEqual(it2, it5);
            Assert::AreEqual(val, v[0]);
        }
    }

    TEST_METHOD(ArrayIterator_decrement) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ArrayIterator<uint32_t> it(&v[2]);
            ArrayIterator<uint32_t> it2(&v[2]);
            ArrayIterator<uint32_t> it3(&v[2]);
            auto it4 = it--;
            auto& it5 = --it2;
            auto val = *it3--;

            Assert::AreEqual(it, it2);
            Assert::AreNotEqual(it, it4);
            Assert::AreEqual(it2, it5);
            Assert::AreEqual(val, v[2]);
        }
    }

    TEST_METHOD(ArrayIterator_arithmetic) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ArrayIterator<uint32_t> it(&v[0]);
            ArrayIterator<uint32_t> it2(&v[2]);
            auto it3 = it + 1;
            auto it4 = 1 + it;
            auto it5 = it2 - 1;
            ptrdiff_t diff = it2 - it;

            Assert::AreEqual(*it3, v[1]);
            Assert::AreEqual(*it4, v[1]);
            Assert::AreEqual(*it5, v[1]);
            Assert::AreEqual(diff, (ptrdiff_t)2);
        }
    }

    TEST_METHOD(ArrayIterator_comparison) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ArrayIterator<uint32_t> it(&v[0]);
            ArrayIterator<uint32_t> it2(&v[2]);
            ArrayIterator<uint32_t> it3(&v[2]);

            Assert::IsTrue(it < it2);
            Assert::IsFalse(it > it2);
            Assert::IsTrue(it <= it2);
            Assert::IsTrue(it2 <= it3);
            Assert::IsFalse(it >= it2);
            Assert::IsTrue(it2 >= it3);
        }
    }

    TEST_METHOD(ArrayIterator_compoundAssignment) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ArrayIterator<uint32_t> it(&v[0]);
            ArrayIterator<uint32_t> it2(&v[2]);
            auto& it3 = it += 2;
            auto& it4 = it2 -= 2;

            Assert::AreEqual(it, it3);
            Assert::AreEqual(it2, it4);
            Assert::AreEqual(*it, v[2]);
            Assert::AreEqual(*it2, v[0]);
        }
    }

    TEST_METHOD(ArrayIterator_offsetDereference) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ArrayIterator<uint32_t> it(&v[0]);
            ArrayIterator<uint32_t> it2(&v[1]);
            auto val = it[2];
            auto val2 = it2[1];

            Assert::AreEqual(val, v[2]);
            Assert::AreEqual(val2, v[2]);
        }
    }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::ArrayIterator<uint32_t>>(const Ghurund::Core::ArrayIterator<uint32_t>& it) {
        return std::format(L"{}", *it).c_str();
    }
}
