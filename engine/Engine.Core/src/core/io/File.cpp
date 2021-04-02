#include "ghcpch.h"
#include "File.h"

namespace Ghurund {
    bool File::exists() const {
        DWORD attributes = GetFileAttributesW(path.toString().Data);

        return (attributes != INVALID_FILE_ATTRIBUTES &&
            !(attributes & FILE_ATTRIBUTE_DIRECTORY));
    }
}
