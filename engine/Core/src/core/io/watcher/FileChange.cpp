#include "ghcpch.h"
#include "FileChange.h"

namespace Ghurund::Core {

    const FileChange& FileChange::ADDED = FileChange(FileChangeEnum::ADDED, "ADDED");
    const FileChange& FileChange::REMOVED = FileChange(FileChangeEnum::REMOVED, "REMOVED");
    const FileChange& FileChange::MODIFIED = FileChange(FileChangeEnum::MODIFIED, "MODIFIED");
    const FileChange& FileChange::RENAMED_FROM = FileChange(FileChangeEnum::RENAMED_FROM, "RENAMED_FROM");
    const FileChange& FileChange::RENAMED_TO = FileChange(FileChangeEnum::RENAMED_TO, "RENAMED_TO");

}