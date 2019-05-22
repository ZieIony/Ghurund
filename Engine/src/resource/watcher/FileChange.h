#pragma once

#include "Ghurund.h"
#include "core/Enum.h"

namespace Ghurund {
    enum class FileChangeEnum {
        ADDED = FILE_ACTION_ADDED,
        REMOVED = FILE_ACTION_REMOVED,
        MODIFIED = FILE_ACTION_MODIFIED,
        RENAMED_FROM = FILE_ACTION_RENAMED_OLD_NAME,
        RENAMED_TO = FILE_ACTION_RENAMED_NEW_NAME,
    };

    class FileChange:public Enum<FileChangeEnum, FileChange> {
    public:
        static const FileChange& ADDED, & REMOVED, & MODIFIED, & RENAMED_FROM, & RENAMED_TO;

        FileChange(FileChangeEnum value, const tchar* name):Enum<FileChangeEnum, FileChange>(value, name) {}
    };
}