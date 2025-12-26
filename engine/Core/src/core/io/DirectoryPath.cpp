#include "ghcpch.h"
#include "DirectoryPath.h"

#include "core/logging/Formatter.h"
#include "core/logging/Logger.h"

namespace Ghurund::Core {
    /*DirectoryPath DirectoryPath::getAbsolutePath() const {
        DWORD bufferLength = (DWORD)(GetCurrentDirectory(0, nullptr) + path.Size + 2); // slash and string terminator
        wchar_t fullPath[MAX_PATH];
        GetFullPathNameW(path.Data, bufferLength, fullPath, nullptr);
        DirectoryPath absolutePath(fullPath);
        return absolutePath;
    }*/

    List<DirectoryPath> DirectoryPath::getDirectories() const {
        List<DirectoryPath> directories;
        WIN32_FIND_DATAW ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;

        hFind = FindFirstFileW(path.Data, &ffd);

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

        hFind = FindFirstFileW(path.Data, &ffd);

        do {
            if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                directories.add(combine(FilePath(ffd.cFileName)));
        } while (FindNextFileW(hFind, &ffd) != 0);

        FindClose(hFind);

        return directories;
    }

    FilePath DirectoryPath::combine(const FilePath& file) const {
        if (file.IsAbsolute)
            return file;
        auto absolutePath = path;
        auto& fileStr = file.toString();
        if (fileStr.startsWith(Path::SEPARATOR)) {
            absolutePath.add(fileStr.Data + 1, fileStr.Length);
        } else {
            absolutePath.add(fileStr);
        }
        while (true) {
            size_t index = absolutePath.find(L"/..");
			if (index == absolutePath.Length)
                break;
			if (index == 0)
                throw InvalidDataException();  // there's something wrong with the path
            size_t prev = absolutePath.findLast(L"/", index - 1);
            if (prev > index)
                throw InvalidDataException();  // there's something wrong with the path
            absolutePath.remove(prev, index - prev + 3);
        }
        absolutePath.removeAll(L"./");
        return FilePath(absolutePath);
    }

    FilePath DirectoryPath::operator/(const FilePath& file) const {
        return combine(file);
    }

}
