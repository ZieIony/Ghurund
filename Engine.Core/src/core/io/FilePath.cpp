#include "FilePath.h"

#include "core/logging/Logger.h"

#include <Shlwapi.h>
#include <tchar.h>

namespace Ghurund {
    FilePath::FilePath(const WString& path):Path(path) {
        DWORD attributes = GetFileAttributesW(path.Data);

        if (attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_DIRECTORY)
            Logger::log(LogType::ERR0R, _T("invalid file path {}\n"), path);
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
