#include "ghcpch.h"
#include "FileChange.h"

namespace Ghurund::Core {

    const FileChange& FileChange::ADDED = FileChange(FileChangeEnum::ADDED, "added");
    const FileChange& FileChange::REMOVED = FileChange(FileChangeEnum::REMOVED, "removed");
    const FileChange& FileChange::MODIFIED = FileChange(FileChangeEnum::MODIFIED, "modified");
    const FileChange& FileChange::RENAMED_FROM = FileChange(FileChangeEnum::RENAMED_FROM, "renamed from");
    const FileChange& FileChange::RENAMED_TO = FileChange(FileChangeEnum::RENAMED_TO, "renamed to");

}