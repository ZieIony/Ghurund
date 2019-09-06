#include "FileChange.h"

namespace Ghurund {

    const FileChange& FileChange::ADDED = FileChange(FileChangeEnum::ADDED, _T("added"));
    const FileChange& FileChange::REMOVED = FileChange(FileChangeEnum::REMOVED, _T("removed"));
    const FileChange& FileChange::MODIFIED = FileChange(FileChangeEnum::MODIFIED, _T("modified"));
    const FileChange& FileChange::RENAMED_FROM = FileChange(FileChangeEnum::RENAMED_FROM, _T("renamed from"));
    const FileChange& FileChange::RENAMED_TO = FileChange(FileChangeEnum::RENAMED_TO, _T("renamed to"));

    const EnumValues<FileChangeEnum, FileChange> FileChange::VALUES = {
        &FileChange::ADDED,
        &FileChange::REMOVED,
        &FileChange::MODIFIED,
        &FileChange::RENAMED_FROM,
        &FileChange::RENAMED_TO
    };

}