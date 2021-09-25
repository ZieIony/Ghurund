#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/Range.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;
    using namespace std;

    TEST_CLASS(RangeTest) {
public:

    TEST_METHOD(Range_inc) {
        auto range = Range<size_t>(0, 3);
        auto iterator = range.begin();
        Assert::AreEqual((size_t)0, *iterator);
        iterator++;
        Assert::AreEqual((size_t)1, *iterator);
        iterator++;
        Assert::AreEqual((size_t)2, *iterator);
        iterator++;
        Assert::AreEqual((size_t)3, *iterator);
        iterator++;
        Assert::AreEqual((size_t)4, *iterator);
        Assert::IsTrue(range.end() == iterator);
    }

    TEST_METHOD(Range_inc_float) {
        auto range = Range<float>(0, 1, 0.5f);
        auto iterator = range.begin();
        Assert::AreEqual(0.0f, *iterator);
        iterator++;
        Assert::AreEqual(0.5f, *iterator);
        iterator++;
        Assert::AreEqual(1.0f, *iterator);
        iterator++;
        Assert::AreEqual(1.5f, *iterator);
        Assert::IsTrue(range.end() == iterator);
    }

    TEST_METHOD(Range_inc_step) {
        auto range = Range<size_t>(0, 3, 2);
        auto iterator = range.begin();
        Assert::AreEqual((size_t)0, *iterator);
        iterator++;
        Assert::AreEqual((size_t)2, *iterator);
        iterator++;
        Assert::AreEqual((size_t)4, *iterator);
        Assert::IsTrue(range.end() == iterator);
    }

    TEST_METHOD(Range_dec) {
        auto range = Range<int>(3, 0, 1);
        auto iterator = range.begin();
        Assert::AreEqual(3, *iterator);
        iterator++;
        Assert::AreEqual(2, *iterator);
        iterator++;
        Assert::AreEqual(1, *iterator);
        iterator++;
        Assert::AreEqual(0, *iterator);
        iterator++;
        Assert::AreEqual(-1, *iterator);
        Assert::IsTrue(range.end() == iterator);
    }

    TEST_METHOD(Range_dec_unsigned) {
        auto range = Range<size_t>(3, 0, 1);
        auto iterator = range.begin();
        Assert::AreEqual((size_t)3, *iterator);
        iterator++;
        Assert::AreEqual((size_t)2, *iterator);
        iterator++;
        Assert::AreEqual((size_t)1, *iterator);
        iterator++;
        Assert::AreEqual((size_t)0, *iterator);
        iterator++;
        Assert::AreEqual((size_t)-1, *iterator);
        Assert::IsTrue(range.end() == iterator);
    }

    TEST_METHOD(Range_dec_autoStep) {
        auto range = Range<int>(3, 0);
        auto iterator = range.begin();
        Assert::AreEqual(3, *iterator);
        iterator++;
        Assert::AreEqual(2, *iterator);
        iterator++;
        Assert::AreEqual(1, *iterator);
        iterator++;
        Assert::AreEqual(0, *iterator);
        iterator++;
        Assert::AreEqual(-1, *iterator);
        Assert::IsTrue(range.end() == iterator);
    }

    TEST_METHOD(Range_bigStep) {
        auto func = [] { Range<int>(3, 0, 5); };
        Assert::ExpectException<std::invalid_argument>(func);
    }

    TEST_METHOD(Range_negativeStep) {
        auto func = [] { Range<float>(3, 0, -1.0f); };
        Assert::ExpectException<std::invalid_argument>(func);
    }

    TEST_METHOD(Range_zeroStep) {
        auto func = [] { Range<int>(3, 0, 0); };
        Assert::ExpectException<std::invalid_argument>(func);
    }
    };
}
