#pragma once

#include "Ghurund.h"
#include "core/FunctionQueue.h"
#include "collection/String.h"
#include "collection/Map.h"
#include "FileChange.h"
#include "core/Buffer.h"
#include "core/WorkerThread.h"

namespace Ghurund {
    class DirectoryWatch {
    private:
        HANDLE dirHandle;
        OVERLAPPED overlapped;
        String directory;
        Buffer buffer;

        WorkerThread delayThread;

        Map<String, std::function<void(const String &fileName, const FileChange)>> files;

        void fileChanged(Buffer &buffer);

        static void CALLBACK notificationCompletion(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped);

    public:
        DirectoryWatch(String &dir):directory(dir), buffer(Buffer(10*1024)) {
            overlapped.hEvent = this;

            dirHandle = ::CreateFile(directory, FILE_LIST_DIRECTORY, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL,
                                     OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED, NULL);

            delayThread.start();
        }

        ~DirectoryWatch();

        void addFile(const String &file, std::function<void(const String &fileName, const FileChange)> fileChangedHandler) {
            files.set(file, fileChangedHandler);
        }

        void removeFile(const String &file) {
            files.remove(file);
        }

        size_t getFileCount() {
            return files.Size;
        }

        __declspec(property(get = getFileCount)) size_t FileCount;

        void readChanges();

        const String &getDirectory() {
            return directory;
        }

        __declspec(property(get = getDirectory)) String &Directory;
    };
}