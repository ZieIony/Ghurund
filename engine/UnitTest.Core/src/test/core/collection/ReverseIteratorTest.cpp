#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"
#include "test/MemoryGuard.h"
#include "test/TestClass.h"

#include "core/collection/iterator/ReverseArrayIterator.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace std;

    // https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
    TEST_CLASS(ReverseArrayIteratorTest) {
public:

    TEST_METHOD(ReverseArrayIterator_defaultConstructor) {
        MemoryGuard guard;
        {
            ReverseArrayIterator<uint32_t> it;
        }
    }

    TEST_METHOD(ReverseArrayIterator_constructor) {
        MemoryGuard guard;
        {
            uint32_t v[2] = { 0,1 };
            ReverseArrayIterator<uint32_t> it(&v[0]);
        }
    }

    TEST_METHOD(ReverseArrayIterator_copyConstructor) {
        MemoryGuard guard;
        {
            const ReverseArrayIterator<uint32_t> it;
            ReverseArrayIterator<uint32_t> it2(it);
        }
    }

    TEST_METHOD(ReverseArrayIterator_assignment) {
        MemoryGuard guard;
        {
            ReverseArrayIterator<uint32_t> it;
            const ReverseArrayIterator<uint32_t> it2;
            it = it2;
        }
    }

    TEST_METHOD(ReverseArrayIterator_equality) {
        MemoryGuard guard;
        {
            uint32_t v[2] = { 0,1 };
            ReverseArrayIterator<uint32_t> it(&v[0]);
            ReverseArrayIterator<uint32_t> it2(&v[0]);
            ReverseArrayIterator<uint32_t> it3(&v[1]);

            Assert::IsTrue(it == it2);
            Assert::IsFalse(it == it3);
            Assert::IsFalse(it != it2);
            Assert::IsTrue(it != it3);
        }
    }

    TEST_METHOD(ReverseArrayIterator_dereference) {
        MemoryGuard guard;
        {
            SimpleTestClass v[2] = { {},{} };
            ReverseArrayIterator<SimpleTestClass> it(&v[0]);
            auto& a = *it;
            auto b = it->val;
        }
        {
            uint32_t v[2] = { 0,1 };
            ReverseArrayIterator<uint32_t> it(&v[0]);
            *it = 3;

            Assert::AreEqual(3u, v[0]);
        }
    }

    TEST_METHOD(ReverseArrayIterator_increment) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ReverseArrayIterator<uint32_t> it(&v[2]);
            ReverseArrayIterator<uint32_t> it2(&v[2]);
            ReverseArrayIterator<uint32_t> it3(&v[2]);
            auto it4 = it++;
            auto& it5 = ++it2;
            auto val = *it3++;

            Assert::AreEqual(it, it2);
            Assert::AreNotEqual(it, it4);
            Assert::AreEqual(it2, it5);
            Assert::AreEqual(val, v[2]);
        }
    }

    TEST_METHOD(ReverseArrayIterator_decrement) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ReverseArrayIterator<uint32_t> it(&v[0]);
            ReverseArrayIterator<uint32_t> it2(&v[0]);
            ReverseArrayIterator<uint32_t> it3(&v[0]);
            auto it4 = it--;
            auto& it5 = --it2;
            auto val = *it3--;

            Assert::AreEqual(it, it2);
            Assert::AreNotEqual(it, it4);
            Assert::AreEqual(it2, it5);
            Assert::AreEqual(val, v[0]);
        }
    }

    TEST_METHOD(ReverseArrayIterator_arithmetic) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ReverseArrayIterator<uint32_t> it(&v[2]);
            ReverseArrayIterator<uint32_t> it2(&v[0]);
            auto it3 = it + 1;
            auto it4 = 1 + it;
            auto it5 = it2 - 1;
            auto diff = it2 - it;

            Assert::AreEqual(*it3, v[1]);
            Assert::AreEqual(*it4, v[1]);
            Assert::AreEqual(*it5, v[1]);
            Assert::AreEqual(diff, (ptrdiff_t)2);
        }
    }

    TEST_METHOD(ReverseArrayIterator_comparison) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ReverseArrayIterator<uint32_t> it(&v[2]);
            ReverseArrayIterator<uint32_t> it2(&v[0]);
            ReverseArrayIterator<uint32_t> it3(&v[0]);

            Assert::IsTrue(it < it2);
            Assert::IsFalse(it > it2);
            Assert::IsTrue(it <= it2);
            Assert::IsTrue(it2 <= it3);
            Assert::IsFalse(it >= it2);
            Assert::IsTrue(it2 >= it3);
        }
    }

    TEST_METHOD(ReverseArrayIterator_compoundAssignment) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ReverseArrayIterator<uint32_t> it(&v[2]);
            ReverseArrayIterator<uint32_t> it2(&v[0]);
            auto& it3 = it += 2;
            auto& it4 = it2 -= 2;

            Assert::AreEqual(it, it3);
            Assert::AreEqual(it2, it4);
            Assert::AreEqual(*it, v[0]);
            Assert::AreEqual(*it2, v[2]);
        }
    }

    TEST_METHOD(ReverseArrayIterator_offsetDereference) {
        MemoryGuard guard;
        {
            uint32_t v[3] = { 0,1,2 };
            ReverseArrayIterator<uint32_t> it(&v[0]);
            ReverseArrayIterator<uint32_t> it2(&v[1]);
            auto val = it[2];
            auto val2 = it2[1];

            Assert::AreEqual(val, v[2]);
            Assert::AreEqual(val2, v[2]);
        }
    }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::ReverseArrayIterator<uint32_t>>(const Ghurund::Core::ReverseArrayIterator<uint32_t>& t) {
        return L"ReverseArrayIterator<uint32_t>";
    }
}
