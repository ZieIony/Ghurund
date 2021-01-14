#pragma once

#include "Path.h"

namespace Ghurund {

    class DirectoryPath:public Path {
    public:
        DirectoryPath(const WString& path);

        inline DirectoryPath getRelativePath(const DirectoryPath& dir) const {
            if (path.startsWith(dir.toString().Data))
                return path.substring(dir.Length);
            return path;
        }

        DirectoryPath getAbsolutePath() const;

        __declspec(property(get = getAbsolutePath)) DirectoryPath AbsolutePath;
    };
}