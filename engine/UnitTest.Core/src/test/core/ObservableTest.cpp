#include "pch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "core/Observable.h"
#include "core/BindableObservable.h"
#include "core/SharedPointer.h"
#include "core/string/String.h"
#include "core/string/TextConversionUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(ObservableTest) {
public:

    TEST_METHOD(Observable_set) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> observable = String(_T("empty"));

            Assert::AreEqual(observable.Value, String(_T("empty")));

            observable = username;

            Assert::AreEqual(username, observable.Value);
        }
    }

    TEST_METHOD(Observable_observe) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> observable = String(_T("empty"));
            uint32_t called = 0;
            observable.add([&](const String& value) {
                called++;
                Assert::AreEqual(value, observable.Value);
            });

            observable = username;

            Assert::AreEqual(called, 2u);
        }
    }

    TEST_METHOD(Observable_observeAfterSet) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> observable = String(_T("empty"));
            uint32_t called = 0;

            observable = username;
            observable.add([&](const String& value) {
                called++;
                Assert::AreEqual(value, observable.Value);
            });

            Assert::AreEqual(called, 1u);
        }
    }

    TEST_METHOD(Observable_observeSameValue) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> observable = String(_T("empty"));
            uint32_t called = 0;
            observable.add([&](const String& value) {
                called++;
                Assert::AreEqual(value, observable.Value);
            });

            observable = username;

            Assert::AreEqual(called, 2u);

            observable = username;

            Assert::AreEqual(called, 2u);
        }
    }

    TEST_METHOD(Observable_observeHandler) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> observable = String(_T("empty"));
            uint32_t called = 0;
            SharedPointer<ObservableHandler<String>> handler = ghnew ObservableHandler<String>([&](const String& value) {
                called++;
                Assert::AreEqual(value, observable.Value);
            });
            observable.add(handler);

            observable = username;

            Assert::AreEqual(called, 2u);
        }
    }

    TEST_METHOD(Observable_handlerRemove) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> observable = String(_T("empty"));
            uint32_t called = 0;
            uint32_t calledFromHandler = 0;
            observable.add([&](const String& value) {
                called++;
                Assert::AreEqual(value, observable.Value);
            });
            SharedPointer<ObservableHandler<String>> handler = ghnew ObservableHandler<String>([&](const String& value) {
                calledFromHandler++;
                Assert::AreEqual(value, observable.Value);
            });
            observable.add(handler);
            observable.remove(*handler);

            observable = username;

            Assert::AreEqual(called, 2u);
            Assert::AreEqual(calledFromHandler, 1u);
        }
    }

    TEST_METHOD(Observable_clear) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> observable = String(_T("empty"));
            uint32_t called = 0;
            observable.add([&](const String& value) {
                called++;
                Assert::AreEqual(value, observable.Value);
            });
            SharedPointer<ObservableHandler<String>> handler = ghnew ObservableHandler<String>([&](const String& value) {
                called++;
                Assert::AreEqual(value, observable.Value);
            });
            observable.add(handler);
            observable.clear();

            observable = username;

            Assert::AreEqual(called, 2u);
        }
    }

    TEST_METHOD(BindableObservable_bind) {
        MemoryGuard guard;
        {
            String username = _T("username");
            BindableObservable<String> observable = String(_T("empty"));
            Observable<String> source = String(_T("empty"));
            uint32_t called = 0;
            observable.bind(source);
            observable.add([&](const String& value) {
                called++;
            });

            source = username;

            Assert::AreEqual(username, observable.Value);
            Assert::AreEqual(username, source.Value);
            Assert::AreEqual(called, 2u);
        }
    }

    TEST_METHOD(BindableObservable_bind_destruct) {
        MemoryGuard guard;
        {
            String username = _T("username");
            Observable<String> source = String(_T("empty"));
            uint32_t called = 0;
            {
                BindableObservable<String> observable = String(_T("empty"));
                observable.bind(source);
                observable.add([&](const String& value) {
                    called++;
                });
            }

            source = username;

            Assert::AreEqual(username, source.Value);
            Assert::AreEqual(called, 1u);
        }
    }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::String>(const Ghurund::Core::String& t) {
        return convertText<tchar, wchar_t>(t).Data;
    }
}