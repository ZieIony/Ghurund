#include "pch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "core/Float.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;

    TEST_CLASS(DataParsingTest) {
public:

    TEST_METHOD(parseFloat) {
        float val = parse<float>("5.0");
        Assert::AreEqual(5.0f, val);
    }
    };
}