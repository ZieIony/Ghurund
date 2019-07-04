#pragma once

#include "core/FunctionQueue.h"
#include "collection/String.h"
#include "collection/Map.h"
#include "FileChange.h"
#include "core/Buffer.h"
#include "core/WorkerThread.h"
#include "core/FilePath.h"

namespace Ghurund {
    class DirectoryWatch {
    private:
        HANDLE dirHandle;
        OVERLAPPED overlapped;
        DirectoryPath directory;
        Buffer buffer;

        WorkerThread delayThread;

        Map<UnicodeString, std::function<void(const FilePath &path, const FileChange&)>> files;

        void fileChanged(Buffer &buffer);

        static void CALLBACK notificationCompletion(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped);

    public:
        DirectoryWatch(const DirectoryPath &dir):directory(dir), buffer(Buffer(10*1024)) {
            overlapped.hEvent = this;

            String dirString = directory.get();
            dirHandle = ::CreateFile(dirString, FILE_LIST_DIRECTORY, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL,
                                     OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED, NULL);

            delayThread.start();
        }

        ~DirectoryWatch();

        void addFile(const FilePath &path, std::function<void(const FilePath &path, const FileChange&)> fileChangedHandler) {
            files.set(path.FileName, fileChangedHandler);
        }

        void removeFile(const FilePath &path) {
            files.remove(path.FileName);
        }

        size_t getFileCount() {
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