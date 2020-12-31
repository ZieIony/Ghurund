#include "FilePath.h"

#include "application/log/Logger.h"

namespace Ghurund {
    FilePath::FilePath(const WString& path):Path(path) {
        DWORD attributes = GetFileAttributesW(path);

        if (attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_DIRECTORY)
            Logger::log(LogType::ERR0R, _T("invalid file path {}\n"), String(path.getData()));
    }
}
