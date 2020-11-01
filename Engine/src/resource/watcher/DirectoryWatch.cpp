#include "DirectoryWatch.h"
#include "application/log/Logger.h"

namespace Ghurund {
    void DirectoryWatch::fileChanged(Buffer& buffer) {
        int offset = 0;
        while (true) {
            FILE_NOTIFY_INFORMATION& fni = *(FILE_NOTIFY_INFORMATION*)(buffer.Data + offset);
            UnicodeString fileName(fni.FileName, fni.FileNameLength / sizeof(wchar_t));

            if (files.contains(fileName)) {
                DWORD action = fni.Action;
                delayThread.remove(fileName);
                Task* task = ghnew Task(fileName, [fileName, action, this] {
                    const FileChange& change = FileChange::VALUES[(FileChangeEnum)action];
                    Logger::log(LogType::INFO, S("file changed: ") + fileName + ", action: " + change.Name + "\n");
                    files[fileName](fileName, change);
                    return Status::OK;
                    });
                delayThread.post(task, 200);
                task->release();
            }

            if (fni.NextEntryOffset == 0)
                break;

            offset += fni.NextEntryOffset;
        };
    }

    void DirectoryWatch::notificationCompletion(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped) {
        DirectoryWatch* watch = (DirectoryWatch*)overlapped->hEvent;

        if (errorCode == ERROR_OPERATION_ABORTED)
            return;

        if (numberOfBytesTransfered == 0)
            return;

        Buffer buffer2(watch->buffer);
        watch->readChanges();
        watch->fileChanged(buffer2);
    }

    DirectoryWatch::~DirectoryWatch() {
        delayThread.finish();
        CancelIo(dirHandle);
        CloseHandle(dirHandle);
    }

    void DirectoryWatch::readChanges() {
        DWORD bytesReturned = 0;
        buffer.zero();

        auto filter = FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME;
        bool success = 0 != ReadDirectoryChangesW(dirHandle, buffer.Data, (DWORD)buffer.Size, false, filter,
            &bytesReturned, &overlapped, &notificationCompletion);

        if (!success)
            Logger::log(LogType::ERR0R, _T("Failed to watch for file changes\n"));
    }
}