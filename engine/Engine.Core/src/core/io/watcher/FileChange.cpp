#include "ghcpch.h"
#include "FileChange.h"

namespace Ghurund {

    const FileChange& FileChange::ADDED = FileChange(FileChangeEnum::ADDED, "added");
    const FileChange& FileChange::REMOVED = FileChange(FileChangeEnum::REMOVED, "removed");
    const FileChange& FileChange::MODIFIED = FileChange(FileChangeEnum::MODIFIED, "modified");
    const FileChange& FileChange::RENAMED_FROM = FileChange(FileChangeEnum::RENAMED_FROM, "renamed from");
    const FileChange& FileChange::RENAMED_TO = FileChange(FileChangeEnum::RENAMED_TO, "renamed to");

    const EnumValues<FileChangeEnum, FileChange> FileChange::VALUES = {
        &FileChange::ADDED,
        &FileChange::REMOVED,
        &FileChange::MODIFIED,
        &FileChange::RENAMED_FROM,
        &FileChange::RENAMED_TO
    };

}