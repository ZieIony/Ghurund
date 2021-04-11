#pragma once

#include "Path.h"

#include <pathcch.h>
#include <Shlwapi.h>

namespace Ghurund {
    class DirectoryPath;

    class FilePath:public Path {
    private:
        mutable WString fileName;

    public:
        FilePath(const WString& path):Path(path) {}

        FilePath(const FilePath& other):Path(other.path) {}

        FilePath(FilePath&& other) noexcept:Path(std::move(other)) {}

        FilePath& operator=(const FilePath& other) {
            if (this == &other)
                return *this;
            Path::operator=(other);
            fileName = other.fileName;
            return *this;
        }

        FilePath& operator=(FilePath&& other) noexcept {
            if (this == &other)
                return *this;
            Path::operator=(other);
            fileName = std::move(other.fileName);
            return *this;
        }

        DirectoryPath getDirectory() const;

        __declspec(property(get = getDirectory)) DirectoryPath Directory;

        inline const WString& getFileName() const {
            if (fileName.Empty) {
                wchar_t* pathCopy = ghnew wchar_t[path.Length];
                memcpy(pathCopy, path.Data, path.Length * sizeof(wchar_t));
                PathStripPathW(pathCopy);
                fileName = pathCopy;
                delete pathCopy;
            }
            return fileName;
        }

        __declspec(property(get = getFileName)) const WString& FileName;

        FilePath getRelativePath(const DirectoryPath& dir) const;

        FilePath getAbsolutePath() const;

        __declspec(property(get = getAbsolutePath)) FilePath AbsolutePath;
    };
}