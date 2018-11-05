#pragma once

#include "Ghurund.h"

namespace Ghurund {
    enum class FileChange {
        ADDED = FILE_ACTION_ADDED,
        REMOVED = FILE_ACTION_REMOVED,
        MODIFIED = FILE_ACTION_MODIFIED,
        RENAMED = FILE_ACTION_RENAMED_OLD_NAME,
        RENAMED_NEW = FILE_ACTION_RENAMED_NEW_NAME,
    };
}