#pragma once

#include "Path.h"

namespace Ghurund {

    class DirectoryPath:public Path {
    public:
        DirectoryPath(const UnicodeString &path):Path(path) {
            DWORD attributes = GetFileAttributesW(path);

            if(attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY))
                Logger::log(_T("invalid directory path %s\n"), String(path).getData());

            if(!path.endsWith(L"/")&&!path.endsWith(L"\\"))
                this->path.add(L'\\');
        }

        DirectoryPath getRelativePath(const DirectoryPath &dir) const {
            if(path.startsWith(dir))
                return path.subString(dir.Length);
            return path;
        }

        DirectoryPath getAbsolutePath() const {
            int bufferLength = GetCurrentDirectory(0, nullptr)+path.Size+2; // slash and string terminator
            wchar_t *fullPath = ghnew wchar_t[bufferLength];
            GetFullPathNameW(path, bufferLength, fullPath, nullptr);
            DirectoryPath absolutePath(fullPath);
            delete[] fullPath;
            return absolutePath;
        }

        __declspec(property(get = getAbsolutePath)) DirectoryPath AbsolutePath;
    };
}