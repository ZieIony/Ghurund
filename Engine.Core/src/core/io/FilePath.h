#pragma once

#include "DirectoryPath.h"

namespace Ghurund {

    class FilePath:public Path {
    public:
        FilePath(const DirectoryPath& dirPath, const WString& fileName):Path(dirPath.toString()) {
            path.add(fileName.Data);
        }

        FilePath(const wchar_t* path):FilePath(WString(path)) {}

        FilePath(const WString& path);

        FilePath(const FilePath & path):Path(path.toString()) {}

        DirectoryPath getDirectory() const {
            size_t index = path.findLast(L"\\");
            if (index != path.Size)
                return path.substring(0, index);
            return path;
        }

        __declspec(property(get = getDirectory)) DirectoryPath Directory;

        inline WString getFileName() const {
            size_t index = path.findLast(L"\\");
            if (index != path.Size)
                return path.substring(index + 1);
            return path;
        }

        __declspec(property(get = getFileName)) WString FileName;

        FilePath getRelativePath(const DirectoryPath& dir) const;

        FilePath getAbsolutePath() const;

        __declspec(property(get = getAbsolutePath)) FilePath AbsolutePath;
    };
}