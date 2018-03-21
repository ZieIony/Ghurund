#pragma once

#include "Ghurund.h"
#include "core/FunctionQueue.h"
#include "collection/String.h"
#include "collection/List.h"

namespace Ghurund {
    class DirectoryWatch {
    private:
        HANDLE dirHandle;
        OVERLAPPED overlapped;
        tchar *directory = nullptr;
        FILE_NOTIFY_INFORMATION buffer[1024];
        List<String> files;
        std::function<void(const String&, DWORD)> fileChangedHandler;

        void fileChanged();

        static void CALLBACK notificationCompletion(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped);

    public:
        DirectoryWatch(tchar *dir, std::function<void(const String&, DWORD)> fileChangedHandler);

        ~DirectoryWatch();

        void addFile(const String &file) {
            files.add(file);
        }

        void removeFile(const String &file) {
            files.remove(file);
        }

        size_t getFileCount() {
            return files.Size;
        }

        void readChanges();

        const tchar *getDirectory() {
            return directory;
        }

    };
}