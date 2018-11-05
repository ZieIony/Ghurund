#include "DirectoryWatch.h"
#include "core/Logger.h"

namespace Ghurund {
    void DirectoryWatch::fileChanged(Buffer &buffer) {
        int offset = 0;
        while(true) {
            FILE_NOTIFY_INFORMATION &fni = *(FILE_NOTIFY_INFORMATION*)(buffer.Data+offset);
            String fileName(fni.FileName, fni.FileNameLength/sizeof(wchar_t));

            if(files.contains(fileName)) {
                Logger::log(_T("file changed: %s, action: %i\n"), fileName.getData(), fni.Action);
                files[fileName](fileName, (FileChange)fni.Action);
            }

            if(fni.NextEntryOffset==0)
                break;

            offset += fni.NextEntryOffset;
        };
    }

    void DirectoryWatch::notificationCompletion(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped) {
        DirectoryWatch *watch = (DirectoryWatch*)overlapped->hEvent;

        if(errorCode == ERROR_OPERATION_ABORTED)
            return;

        if(numberOfBytesTransfered==0)
            return;

        Buffer buffer2(watch->buffer);
        watch->readChanges();
        watch->fileChanged(buffer2);
    }

    DirectoryWatch::~DirectoryWatch() {
        CancelIo(dirHandle);
        CloseHandle(dirHandle);
    }

    void DirectoryWatch::readChanges() {
        DWORD bytesReturned = 0;
        buffer.zero();

        auto filter = FILE_NOTIFY_CHANGE_CREATION|FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_FILE_NAME;
        bool success = 0!=ReadDirectoryChangesW(dirHandle, buffer.Data, buffer.Size, false, filter,
                                                &bytesReturned, &overlapped, &notificationCompletion);

        if(!success)
            Logger::log(_T("Failed to watch for file changes\n"));
    }
}