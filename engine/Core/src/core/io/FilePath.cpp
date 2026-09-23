#include "ghcpch.h"
#include "FilePath.h"

#include "core/logging/Formatter.h"

namespace Ghurund::Core {
    DirectoryPath FilePath::getDirectory() const {
        return DirectoryPath(path.substring(0, path.findLast(Path::SEPARATOR)));
    }

    FilePath FilePath::getRelativePath(const DirectoryPath& dir) const {
        if (path.startsWith(dir.toString()))
            return FilePath(path.substring(0, dir.toString().Length));
        return *this;
    }

    /*FilePath FilePath::getAbsolutePath() const {
        wchar_t fullPath[MAX_PATH];
        GetFullPathNameW(path.Data, MAX_PATH, fullPath, nullptr);
        return FilePath(fullPath);
    }*/
}
