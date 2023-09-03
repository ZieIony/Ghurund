#include "pch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "core/math/Float.h"
#include "core/math/Int.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;

    TEST_CLASS(DataParsingTest) {
public:

    TEST_METHOD(parseFloat) {
        float val = parse<float>("5.1");
        Assert::AreEqual(5.1f, val);
    }

    TEST_METHOD(parseDouble) {
        double val = parse<double>("5.1");
        Assert::AreEqual(5.1, val);
    }

    TEST_METHOD(parseUint32) {
        uint32_t val = parse<uint32_t>("56");
        Assert::AreEqual(56ui32, val);
    }

    TEST_METHOD(parseInt) {
        int val = parse<int>("56");
        Assert::AreEqual(56, val);
    }
    };
}