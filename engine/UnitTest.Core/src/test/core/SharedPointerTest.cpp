#include "utcpch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "core/SharedPointer.h"
#include "core/reflection/StandardTypes.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(SharedPointerTest) {
public:

    TEST_METHOD(SharedPointer_empty) {
        MemoryGuard guard;
        {
            SharedPointer<bool> ptr;
            Assert::IsNull(ptr.get());
            Assert::AreEqual((uint32_t)1, ptr.ReferenceCount);
        }
    }

    TEST_METHOD(SharedPointer_oneRef) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            SharedPointer<bool> ptr(b);
            Assert::AreEqual(b, ptr.get());
            Assert::AreEqual((uint32_t)1, ptr.ReferenceCount);
        }
    }

    TEST_METHOD(SharedPointer_twoRefs) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            SharedPointer<bool> ptr(b);
            SharedPointer<bool> ptr2 = ptr;
            Assert::AreEqual(b, ptr.get());
            Assert::AreEqual(b, ptr2.get());
            Assert::AreEqual((uint32_t)2, ptr.ReferenceCount);
            Assert::AreEqual((uint32_t)2, ptr2.ReferenceCount);
        }
    }

    TEST_METHOD(SharedPointer_twoRefsOne) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            SharedPointer<bool> ptr(b);
            {
                SharedPointer<bool> ptr2 = ptr;
            }
            Assert::AreEqual(b, ptr.get());
            Assert::AreEqual((uint32_t)1, ptr.ReferenceCount);
        }
    }

    TEST_METHOD(SharedPointer_twoRefsSecondLeft) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            SharedPointer<bool> ptr2;
            {
                SharedPointer<bool> ptr(b);
                ptr2 = ptr;
            }
            Assert::AreEqual(b, ptr2.get());
            Assert::AreEqual((uint32_t)1, ptr2.ReferenceCount);
        }
    }

    TEST_METHOD(SharedPointer_replaceValue) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            SharedPointer<bool> ptr(b);
            bool* b2 = ghnew bool(false);
            ptr.set(b2);
            Assert::AreEqual(b2, ptr.get());
            Assert::AreEqual((uint32_t)1, ptr.ReferenceCount);
        }
    }

    TEST_METHOD(SharedPointer_equalsSame) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            SharedPointer<bool> ptr(b);
            SharedPointer<bool> ptr2 = ptr;
            Assert::IsTrue(ptr == ptr2);
        }
    }

    TEST_METHOD(SharedPointer_equalsDiffrent) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            bool* b2 = ghnew bool(false);
            SharedPointer<bool> ptr(b);
            SharedPointer<bool> ptr2(b2);
            Assert::IsFalse(ptr == ptr2);
            Assert::IsTrue(ptr != ptr2);
        }
    }

    TEST_METHOD(SharedPointer_equalsNull) {
        MemoryGuard guard;
        {
            bool* b = ghnew bool(false);
            SharedPointer<bool> ptr(b);
            SharedPointer<bool> ptr2;
            Assert::IsTrue(ptr != nullptr);
            Assert::IsTrue(ptr2 == nullptr);
        }
    }
    };
}
