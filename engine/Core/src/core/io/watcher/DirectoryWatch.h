#pragma once

#include "FileChange.h"

#include "core/Buffer.h"
#include "core/collection/Set.h"
#include "core/io/DirectoryPath.h"
#include "core/io/FilePath.h"
#include "core/math/MathUtils.h"
#include "core/string/String.h"
#include "core/Event.h"

namespace Ghurund::Core {
    class DirectoryWatch {
    private:
        HANDLE dirHandle;
        OVERLAPPED overlapped;
        DirectoryPath directory;
        Buffer buffer;

        Set<WString> files;

        void onFileChanged(Buffer &buffer);

        static void CALLBACK notificationCompletion(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped);

    public:
        Event<DirectoryWatch, const FileChange&> fileChanged = *this;

        DirectoryWatch(const DirectoryPath &dir):directory(dir), buffer(Buffer(10_KB)) {
            overlapped.hEvent = this;

            dirHandle = ::CreateFileW(directory.toString().Data, FILE_LIST_DIRECTORY, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL,
                                     OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED, NULL);
        }

        ~DirectoryWatch();

        inline bool containsFile(const FilePath& path) {
            return files.contains(path.FileName.Data);
        }

        inline void addFile(const FilePath &path) {
            files.put(path.FileName.Data);
        }

        inline void removeFile(const FilePath &path) {
            files.remove(path.FileName.Data);
        }

        inline size_t getFileCount() {
            return files.Size;
        }

        __declspec(property(get = getFileCount)) size_t FileCount;

        void readChanges();

        const DirectoryPath &getDirectory() {
            return directory;
        }

        __declspec(property(get = getDirectory)) DirectoryPath &Directory;
    };
}