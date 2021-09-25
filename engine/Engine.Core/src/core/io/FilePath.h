#pragma once

#include "Path.h"

#include <Windows.h>
#include <pathcch.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Pathcch.lib")

namespace Ghurund::Core {
    class DirectoryPath;

    class FilePath:public Path {
    private:
        WString fileName, extension;

    public:
        FilePath(const WString& path):Path(path),
            fileName(PathFindFileNameW(path.Data)),
            extension(PathFindExtensionW(path.Data)) {}

        FilePath(const FilePath& other):Path(other.path),
            fileName(other.fileName),
            extension(other.extension) {}

        FilePath(FilePath&& other) noexcept:Path(std::move(other)),
            fileName(std::move(other.fileName)),
            extension(std::move(other.extension)) {}

        FilePath& operator=(const FilePath& other) {
            if (this == &other)
                return *this;
            Path::operator=(other);
            fileName = other.fileName;
            extension = other.extension;
            return *this;
        }

        FilePath& operator=(FilePath&& other) noexcept {
            if (this == &other)
                return *this;
            Path::operator=(other);
            fileName = std::move(other.fileName);
            extension = std::move(other.extension);
            return *this;
        }

        DirectoryPath getDirectory() const;

        __declspec(property(get = getDirectory)) DirectoryPath Directory;

        inline const WString& getFileName() const {
            return fileName;
        }

        __declspec(property(get = getFileName)) const WString& FileName;

        inline const WString& getExtension() const {
            return extension;
        }

        __declspec(property(get = getExtension)) const WString& Extension;

        FilePath getRelativePath(const DirectoryPath& dir) const;

        FilePath getAbsolutePath() const;

        __declspec(property(get = getAbsolutePath)) FilePath AbsolutePath;
    };
}