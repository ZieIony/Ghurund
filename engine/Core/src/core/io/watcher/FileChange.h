#pragma once

#include <core/io/FilePath.h>

#include <Windows.h>

namespace Ghurund::Core {
    enum class FileChangeType {
        ADDED = FILE_ACTION_ADDED,
        REMOVED = FILE_ACTION_REMOVED,
        MODIFIED = FILE_ACTION_MODIFIED,
        RENAMED_FROM = FILE_ACTION_RENAMED_OLD_NAME,
        RENAMED_TO = FILE_ACTION_RENAMED_NEW_NAME,
    };

    class FileChange {
    private:
        FilePath path;
        FileChangeType type;

    public:
        FileChange(const FilePath& path, FileChangeType type):path(path), type(type) {}

        FileChange(const FileChange& other):path(other.path), type(other.type) {}

		FileChange(FileChange&& other) noexcept:path(std::move(other.path)), type(std::move(other.type)) {}

        inline const FilePath& getPath() const {
            return path;
        }

        __declspec(property(get = getPath)) const FilePath& Path;

        inline FileChangeType getType() const {
            return type;
        }

        __declspec(property(get = getType)) FileChangeType Type;
    };
}
