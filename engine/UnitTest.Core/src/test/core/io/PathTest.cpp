#include "pch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"

#include "core/io/FilePath.h"
#include "core/io/DirectoryPath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::FilePath>(const Ghurund::Core::FilePath& t) {
        return t.toString().Data;
    }
}

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(PathTest) {
public:

    TEST_METHOD(FilePath_test) {
        MemoryGuard guard;
        {
            auto path = FilePath(L"dir\\file.png");

            Assert::AreEqual(L"file.png", path.FileName.Data);
            Assert::AreEqual(L"dir", path.Directory.toString().Data);

            auto path2 = FilePath(path);
            Assert::AreEqual(path, path2);

            path2 = WString(L"dir\\file.jpg");
            Assert::AreEqual(L"dir\\file.jpg", path2.toString().Data);
            Assert::AreNotEqual(path, path2);
        }
    }

    TEST_METHOD(DirectoryPath_combine) {
        MemoryGuard guard;
        {
            auto dir = DirectoryPath(L"dir");
            auto path = dir / FilePath(L"file.png");
            Assert::AreEqual(L"dir\\file.png", path.toString().Data);

            auto dir2 = DirectoryPath(L".");
            auto path2 = dir2 / FilePath(L"dir\\file.png");
            Assert::AreEqual(L"dir\\file.png", path2.toString().Data);
        }
    }

    TEST_METHOD(FilePath_getDirectory) {
        MemoryGuard guard;
        {
            auto path = FilePath(L"c:\\test\\folder\\path\\file.png");
            Assert::AreEqual(L"c:\\test\\folder\\path", path.Directory.toString().Data);
        }
    }

    TEST_METHOD(FilePath_noExtension) {
        MemoryGuard guard;
        {
            auto path = FilePath(L"c:\\test\\folder\\path\\file");
            Assert::AreEqual(L"", path.Extension.Data);
        }
    }
    };
}
