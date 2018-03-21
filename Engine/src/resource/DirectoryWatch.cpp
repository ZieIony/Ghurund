#include "DirectoryWatch.h"
#include "core/Logger.h"

namespace Ghurund {
    void DirectoryWatch::fileChanged() {
        DWORD bytesTransferred;
        GetOverlappedResult(dirHandle, &overlapped, &bytesTransferred, true);
        int i = 0;
        while(true) {
            FILE_NOTIFY_INFORMATION &fni = buffer[i++];
            tchar *fileName;
#ifndef UNICODE
            wchar_t *copy = new wchar_t[fni.FileNameLength/sizeof(wchar_t)+1];
            memcpy(copy, fni.FileName, fni.FileNameLength+sizeof(wchar_t));
            copy[fni.FileNameLength/sizeof(wchar_t)] = 0;
            toASCII(&fileName, copy, 0);
            delete[] copy;
#else
            fileName = new tchar[fni.FileNameLength/sizeof(tchar)+1];
            fileName[fni.FileNameLength/sizeof(wchar_t)] = 0;
            memcpy(fileName, fni.FileName, fni.FileNameLength);
#endif

            String fileNameString(fileName);
            if(files.contains(fileNameString)) {
                Logger::log(_T("file changed: %s, action: %i\n"), fileName, fni.Action);
                fileChangedHandler(fileNameString, fni.Action);
            }

            if(fni.NextEntryOffset==0)
                break;
        };
    }

    void DirectoryWatch::notificationCompletion(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped) {
        DirectoryWatch *watch = (DirectoryWatch*)overlapped->hEvent;

        if(errorCode == ERROR_OPERATION_ABORTED) {

        }

        if(numberOfBytesTransfered==0)
            return;

        watch->fileChanged();
        watch->readChanges();
    }

    DirectoryWatch::DirectoryWatch(tchar * dir, std::function<void(const String&, DWORD)> fileChangedHandler):fileChangedHandler(fileChangedHandler) {
        safeCopyStr(&directory, dir);

        overlapped.hEvent = this;

        dirHandle = ::CreateFile(
            directory,           // pointer to the file name
            FILE_LIST_DIRECTORY,    // access (read/write) mode
            FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,         // share mode
            NULL, // security descriptor
            OPEN_EXISTING,         // how to create
            FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED, // file attributes
            NULL);
    }

    DirectoryWatch::~DirectoryWatch() {
        CancelIo(dirHandle);
        CloseHandle(dirHandle);
    }

    void DirectoryWatch::readChanges() {
        DWORD bytesReturned = 0;

        bool success = 0!=ReadDirectoryChangesW(
            dirHandle,                                  // handle to directory
            &buffer,                          // read results buffer
            sizeof(buffer),                       // length of buffer
            false,                                 // monitoring option
            FILE_NOTIFY_CHANGE_CREATION|FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_FILE_NAME,             // filter conditions
            &bytesReturned,              // bytes returned
            &overlapped,                          // overlapped buffer
            &notificationCompletion);

        if(!success)
            Logger::log(_T("Failed to watch for file changes\n"));
    }
}