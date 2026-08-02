#include "ghcpch.h"
#include "DirectoryLibrary.h"

#include "core/logging/Formatter.h"

namespace Ghurund::Core {
    SharedPointer<Buffer> DirectoryLibrary::get(const WString& path) const {
        File file(this->path / FilePath(path));
        if (!file.Exists)
            throw std::invalid_argument(std::format("path \"{}\" doesn't exist", path));
        auto buffer = SharedPointer(ghnew Buffer());
        file.read(*buffer.get());
        return buffer;
    }
}
