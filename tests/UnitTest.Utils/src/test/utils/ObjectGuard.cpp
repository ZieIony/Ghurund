#include "ObjectGuard.h"

#include "core/object/RefCountedObject.h"

#include "CppUnitTest.h"

namespace UnitTest::Utils {
    using namespace Ghurund::Core;
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;

    ObjectGuard::ObjectGuard() {
        allocatedObjects = RefCountedObject::numberOfAllocatedPointers();
    }

    ObjectGuard::~ObjectGuard() {
        auto currentAllocatedObjects = RefCountedObject::numberOfAllocatedPointers();
        if (allocatedObjects != currentAllocatedObjects) {
            RefCountedObject::dumpPointers();
            Assert::AreEqual(allocatedObjects, currentAllocatedObjects, L"unreleased objects detected");
        }
    }
}
