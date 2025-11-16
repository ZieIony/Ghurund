#include "utcpch.h"
#include "CppUnitTest.h"

#include "core/Timer.h"
#include "core/window/SystemWindow.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(SystemWindowTest) {
public:

    TEST_METHOD(SystemWindow_constructDestroy) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
        }
    }

    TEST_METHOD(SystemWindow_properties) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.Position = { 0, 0 };
            window.Size = { 100, 100 };
            window.Title = _T("test");
            Assert::AreEqual(XMINT2{0,0}, window.Position);
            Assert::AreEqual(IntSize{100,100}, window.Size);
            Assert::AreEqual(String(_T("test")), window.Title);
        }
    }

    };
}
