#pragma once

#include "Path.h"
#include "core/string/StringView.h"

#include <Windows.h>
#include <pathcch.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Pathcch.lib")

namespace Ghurund::Core {
    class DirectoryPath;

    class FilePath:public Path {
    private:
        WStringView fileName, extension;

        static inline const wchar_t* getExtensionWithoutDot(const wchar_t* path) {
            const wchar_t* str = PathFindExtensionW(path);
            if (str[0] == '.')
                return str + 1;
            return str;
        }

    public:
        FilePath(const WString& path):Path(path),
            fileName(PathFindFileNameW(this->path.Data)),
            extension(getExtensionWithoutDot(this->path.Data)) {}

        FilePath(const FilePath& other):Path(other.path),
            // copy constructor for StringView just reuses the pointer to its internal char array, which may be destroyed
            fileName(PathFindFileNameW(path.Data)),
            extension(getExtensionWithoutDot(path.Data)) {}

        FilePath(FilePath&& other) noexcept:Path(std::move(other)),
            fileName(std::move(other.fileName)),
            extension(std::move(other.extension)) {}

        FilePath& operator=(const FilePath& other) {
            if (this == &other)
                return *this;
            Path::operator=(other);
            fileName = PathFindFileNameW(path.Data);
            extension = getExtensionWithoutDot(path.Data);
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

        inline const WStringView& getFileName() const {
            return fileName;
        }

        __declspec(property(get = getFileName)) const WStringView& FileName;

        inline const WStringView& getExtension() const {
            return extension;
        }

        __declspec(property(get = getExtension)) const WStringView& Extension;

        FilePath getRelativePath(const DirectoryPath& dir) const;

        FilePath getAbsolutePath() const;

        __declspec(property(get = getAbsolutePath)) FilePath AbsolutePath;
    };
}