#include "pch.h"
#include "CppUnitTest.h"

#include "core/io/FilePath.h"
#include "core/io/DirectoryPath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::FilePath>(const Ghurund::FilePath& t) {
        return t.toString().Data;
    }
}

namespace UnitTest {
    using namespace Ghurund;

    TEST_CLASS(PathTest) {
public:

    TEST_METHOD(FilePath_test) {
        auto path = FilePath(L"dir/file.png");

        Assert::AreEqual(L"file.png", path.FileName.Data);
        Assert::AreEqual(L"dir", path.Directory.toString().Data);

        auto path2 = FilePath(path);
        Assert::AreEqual(path, path2);

        path2 = WString(L"dir/file.jpg");
        Assert::AreEqual(L"dir\\file.jpg", path2.toString().Data);
        Assert::AreNotEqual(path, path2);
    }

    TEST_METHOD(DirectoryPath_test) {
        auto dir = DirectoryPath(L"dir");
        auto path = dir / FilePath(L"file.png");
        Assert::AreEqual(L"dir\\file.png", path.toString().Data);
    }
    };
}
