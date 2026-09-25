#include "ghcpch.h"
#include "DirectoryPath.h"

#include <pathcch.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

namespace Ghurund::Core {
    DirectoryPath DirectoryPath::getCurrentDirectory() {
        DWORD bufferLength = GetCurrentDirectoryW(0, nullptr);
        Array<wchar_t> buffer(bufferLength);
        GetCurrentDirectoryW(bufferLength, &buffer[0]);
        auto path = WString(&buffer[0], bufferLength - 1);
        if (!path.endsWith(L"/"))
            path.add(L'/');
        return DirectoryPath(path);
    }

    DirectoryPath DirectoryPath::getAbsolutePath() const {
        DWORD bufferLength = (DWORD)(GetCurrentDirectory(0, nullptr) + path.Size + 2); // slash and string terminator
        wchar_t fullPath[MAX_PATH];
        GetFullPathNameW(path.Data, bufferLength, fullPath, nullptr);
        DirectoryPath absolutePath(fullPath);
        return absolutePath;
    }

    List<DirectoryPath> DirectoryPath::getDirectories() const {
        List<DirectoryPath> directories;
        WIN32_FIND_DATAW ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        WString query = path + L"*";

        hFind = FindFirstFileW(query.Data, &ffd);
        if (hFind == INVALID_HANDLE_VALUE)
            return {};

        do {
            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                directories.add(combine(DirectoryPath(ffd.cFileName)));
        } while (FindNextFileW(hFind, &ffd) != 0);

        FindClose(hFind);

        return directories;
    }

    List<FilePath> DirectoryPath::getFiles() const {
        List<FilePath> directories;
        WIN32_FIND_DATAW ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        WString query = path + L"*";

        hFind = FindFirstFileW(query.Data, &ffd);
        if (hFind == INVALID_HANDLE_VALUE)
            return {};

        do {
            if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                directories.add(combine(FilePath(ffd.cFileName)));
        } while (FindNextFileW(hFind, &ffd) != 0);

        FindClose(hFind);

        return directories;
    }

    WString DirectoryPath::combineStr(const WString& str) const {
        wchar_t destPath[MAX_PATH];
        DWORD size = MAX_PATH;
        WString pathStr = path;
        WString dirStr = str;
        if (pathStr.startsWith(ResourceManager::LIB_PROTOCOL)) {
            UrlCombineW(pathStr.Data, dirStr.Data, destPath, &size, 0);
        } else {
            pathStr.replaceAll(Path::SEPARATOR, L"\\");
            dirStr.replaceAll(Path::SEPARATOR, L"\\");
            PathCchCombine(destPath, MAX_PATH, pathStr.Data, dirStr.Data);
        }
        return WString(destPath);
    }

    DirectoryPath DirectoryPath::combine(const DirectoryPath& dir) const {
        if (dir.IsAbsolute || dir.IsLibrary)
            return dir;
        return DirectoryPath(combineStr(dir.toString()));
    }

    FilePath DirectoryPath::combine(const FilePath& file) const {
        if (file.IsAbsolute || file.IsLibrary)
            return file;
        return FilePath(combineStr(file.toString()));
    }
}
