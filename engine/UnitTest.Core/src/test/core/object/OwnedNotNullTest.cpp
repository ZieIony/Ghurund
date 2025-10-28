#include "utcpch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "Common.h"
#include "core/object/OwnedNotNull.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(OwnedNotNullTest) {
public:

    TEST_METHOD(SharedPointer_empty) {
        MemoryGuard guard;
        {
            Assert::ExpectException<NullPointerException>([] {
                OwnedNotNull<bool> ptr(nullptr);
            });
        }
    }

    TEST_METHOD(SharedPointer_oneRef) {
        MemoryGuard guard;
        {
            uint32_t* i = ghnew uint32_t(35);
            OwnedNotNull ptr(i);
            Assert::AreEqual((uint32_t)35, *i);
            Assert::AreEqual((uint32_t)35, *&ptr);
        }
    }

    TEST_METHOD(SharedPointer_reset) {
        MemoryGuard guard;
        {
            uint32_t* i = ghnew uint32_t(35);
            OwnedNotNull ptr(i);
            uint32_t* j = ptr.reset();
            Assert::IsNull(&ptr);
            Assert::AreEqual((uint32_t)35, *j);
            delete j;
        }
    }

    TEST_METHOD(SharedPointer_assignment) {
        MemoryGuard guard;
        {
            uint32_t* i = ghnew uint32_t(35);
            OwnedNotNull ptr(i);
            uint32_t* j = ghnew uint32_t(36);
            OwnedNotNull ptr2(j);
            ptr = std::move(ptr2);
            Assert::AreEqual((uint32_t)36, *ptr);
        }
    }
    };
}
