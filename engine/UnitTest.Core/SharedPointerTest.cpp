#include "pch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"
#include "test/TestClass.h"

#include "core/SharedPointer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(SharedPointerTest) {
    public:

        TEST_METHOD(assignment) {
            MemoryGuard guard;
            {
                PointerTestClass* obj = ghnew PointerTestClass();
                obj->addReference();
                SharedPointer<PointerTestClass> ptr(obj);
                ptr = makeShared<PointerTestClass>();

                Assert::IsFalse(obj == ptr.get());
                Assert::AreEqual(1ul, obj->ReferenceCount);
                obj->release();
            }
        }

        TEST_METHOD(listAddRemove) {
            MemoryGuard guard;
            {
                List<SharedPointer<PointerTestClass>> list;
                PointerTestClass* obj = ghnew PointerTestClass();
                obj->addReference();
                list.add(SharedPointer(obj));
                obj->addReference();
                list.remove(SharedPointer(obj));
                Assert::AreEqual(1ul, obj->ReferenceCount);
                obj->release();
            }
        }
    };
}
