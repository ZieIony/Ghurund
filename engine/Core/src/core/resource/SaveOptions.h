#pragma once

namespace Ghurund::Core {
    enum class FileExistsOption {
        OVERWRITE, SKIP, THROW
    };

    struct SaveOptions {
        FileExistsOption fileExistsOption = FileExistsOption::OVERWRITE;
    };
}
