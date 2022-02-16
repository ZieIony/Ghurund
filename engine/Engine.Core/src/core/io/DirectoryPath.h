#pragma once

#include "FilePath.h"
#include "core/collection/List.h"

namespace Ghurund::Core {

    class DirectoryPath:public Path {
    public:
        DirectoryPath(const WString& path):Path(path) {}

        DirectoryPath(const DirectoryPath& path):DirectoryPath(path.path) {}

        DirectoryPath(DirectoryPath&& path) noexcept:Path(std::move(path)) {}

        inline DirectoryPath getRelativePath(const DirectoryPath& dir) const {
            if (path.startsWith(dir.toString().Data))
                return path.substring(dir.Length);
            return path;
        }

        DirectoryPath getAbsolutePath() const;

        __declspec(property(get = getAbsolutePath)) DirectoryPath AbsolutePath;

        inline DirectoryPath combine(const DirectoryPath& dir) const {
            wchar_t destPath[MAX_PATH];
            PathCchCombine(destPath, MAX_PATH, path.Data, dir.toString().Data);
            return DirectoryPath(destPath);
        }

        inline DirectoryPath operator/(const DirectoryPath& dir) const {
            return combine(dir);
        }

        FilePath combine(const FilePath& file) const;

        FilePath operator/(const FilePath& file) const;

        List<DirectoryPath> getDirectories() const;

        __declspec(property(get = getDirectories)) List<DirectoryPath> Directories;

        List<FilePath> getFiles() const;

        __declspec(property(get = getFiles)) List<FilePath> Files;
    };
}