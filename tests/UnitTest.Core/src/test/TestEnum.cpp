#include "utcpch.h"

#include "TestEnum.h"

namespace UnitTest::Utils {
    const TestEnum TestEnum::A = TestEnum(TestEnumEnum::A, "A", 5);
    const TestEnum TestEnum::B = TestEnum(TestEnumEnum::B, "B", 6);
}