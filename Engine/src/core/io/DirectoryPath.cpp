#include "DirectoryPath.h"

#include "application/log/Logger.h"

namespace Ghurund {
    DirectoryPath::DirectoryPath(const UnicodeString& path):Path(path) {
        DWORD attributes = GetFileAttributesW(path);

        if (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY))
            Logger::log(LogType::ERR0R, _T("invalid directory path {}\n"), String(path.getData()));

        if (!path.endsWith(L"/") && !path.endsWith(L"\\"))
            this->path.add(L'\\');
    }

    DirectoryPath DirectoryPath::getAbsolutePath() const {
        DWORD bufferLength = (DWORD)(GetCurrentDirectory(0, nullptr) + path.Size + 2); // slash and string terminator
        wchar_t* fullPath = ghnew wchar_t[bufferLength];
        GetFullPathNameW(path, bufferLength, fullPath, nullptr);
        DirectoryPath absolutePath(fullPath);
        delete[] fullPath;
        return absolutePath;
    }
}
