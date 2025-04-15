#include "pch.h"
#include "CppUnitTest.h"

#include "core/Timer.h"
#include "core/window/SystemWindow.h"
#include "test/MemoryGuard.h"
#include "test/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(SystemWindowTest) {
public:

    TEST_METHOD(SystemWindow_initOnly) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.init();
        }
    }

    TEST_METHOD(SystemWindow_doubleInit) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.init();
        }
    }

    TEST_METHOD(SystemWindow_initUninit) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.init();
            window.uninit();
        }
    }

    TEST_METHOD(SystemWindow_doubleUninit) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.init();
            window.uninit();
            window.uninit();
        }
    }

    TEST_METHOD(SystemWindow_propertiesBeforeInit) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.Position = { 0, 0 };
            window.Size = { 100, 100 };
            window.Title = _T("test");
            window.init();
            Assert::AreEqual(IntPoint{0,0}, window.Position);
            Assert::AreEqual(IntSize{100,100}, window.Size);
            Assert::AreEqual(String(_T("test")), window.Title);
            window.uninit();
        }
    }

    TEST_METHOD(SystemWindow_propertiesAfterInit) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.init();
            window.Position = { 0, 0 };
            window.Size = { 100, 100 };
            window.Title = _T("test");
            Assert::AreEqual(IntPoint{ 0,0 }, window.Position);
            Assert::AreEqual(IntSize{ 100,100 }, window.Size);
            Assert::AreEqual(String(_T("test")), window.Title);
            window.uninit();
        }
    }

    TEST_METHOD(SystemWindow_propertiesAfterUninit) {
        Timer timer;
        MemoryGuard guard;
        {
            SystemWindow window(timer);
            window.init();
            window.uninit();
            window.Position = { 0, 0 };
            window.Size = { 100, 100 };
            window.Title = _T("test");
        }
    }

    };
}
