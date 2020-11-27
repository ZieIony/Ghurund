#pragma once

#include "Path.h"

namespace Ghurund {

    class DirectoryPath:public Path {
    public:
        DirectoryPath(const UnicodeString& path);

        inline DirectoryPath getRelativePath(const DirectoryPath& dir) const {
            if (path.startsWith(dir))
                return path.subString(dir.Length);
            return path;
        }

        DirectoryPath getAbsolutePath() const;

        __declspec(property(get = getAbsolutePath)) DirectoryPath AbsolutePath;
    };
}