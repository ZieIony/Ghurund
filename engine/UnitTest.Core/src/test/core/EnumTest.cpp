#include "utcpch.h"
#include "CppUnitTest.h"

#include <test/MemoryGuard.h>
#include <test/TestEnum.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace std;
    using namespace Ghurund::Core;

    TEST_CLASS(EnumTest) {
public:

    TEST_METHOD(Enum_copy) {
        MemoryGuard guard;
        {
            const TestEnum e = TestEnum::A;
            TestEnum copy = e;

            Assert::IsTrue(e == copy);
        }
    }

    TEST_METHOD(Enum_fromName) {
        MemoryGuard guard;
        {
            const TestEnum e = TestEnum::fromName("A");

            Assert::IsTrue(e == TestEnum::A);
        }
    }

    TEST_METHOD(Enum_fromValue) {
        MemoryGuard guard;
        {
            const TestEnum e = TestEnum::fromValue(TestEnumEnum::A);

            Assert::IsTrue(e == TestEnum::A);
        }
    }
    };
}
