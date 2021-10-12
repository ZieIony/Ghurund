#include "ghcpch.h"
#include "FilePath.h"

#include "core/logging/Formatter.h"
#include "core/logging/Logger.h"

#include <Shlwapi.h>

namespace Ghurund::Core {
    DirectoryPath FilePath::getDirectory() const {
        wchar_t* pathCopy = copyStr(path.Data);
        PathCchRemoveFileSpec(pathCopy, path.Size);
        DirectoryPath dir = WString(pathCopy);
        delete[] pathCopy;
        return dir;
    }

    FilePath FilePath::getRelativePath(const DirectoryPath& dir) const {
        wchar_t relativePathStr[MAX_PATH];
        BOOL success = PathRelativePathToW(relativePathStr, dir.toString().getData(), FILE_ATTRIBUTE_DIRECTORY, path.getData(), FILE_ATTRIBUTE_NORMAL);
        if (success)
            return FilePath(relativePathStr);
        return *this;
    }

    FilePath FilePath::getAbsolutePath() const {
        wchar_t fullPath[MAX_PATH];
        GetFullPathNameW(path.Data, MAX_PATH, fullPath, nullptr);
        return FilePath(fullPath);
    }
}
