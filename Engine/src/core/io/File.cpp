#include "File.h"

#include <Windows.h>

namespace Ghurund {
    bool File::exists() const {
        DWORD attributes = GetFileAttributesW(path);

        return (attributes != INVALID_FILE_ATTRIBUTES &&
            !(attributes & FILE_ATTRIBUTE_DIRECTORY));
    }
}
