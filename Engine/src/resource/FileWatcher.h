#pragma once

#include "Ghurund.h"
#include "core/FunctionQueue.h"
#include "collection/String.h"
#include "collection/List.h"
#include "DirectoryWatch.h"
#include "core/Thread.h"

namespace Ghurund {

    class FileWatcher {
    private:
        std::function<void(const String&, DWORD)> fileChangedHandler;
        APCThread thread;
        List<DirectoryWatch*> watches;

        static void CALLBACK readChangesProc(__in  ULONG_PTR arg);

        void getFullPathName(tchar **fullDir, const tchar *file);

        DirectoryWatch *findWatch(const tchar *fullPath);

        void getFullPath(tchar **fullPath, const tchar *file);

    public:
        FileWatcher(std::function<void(const String&, DWORD)> fileChangedHandler);

        ~FileWatcher();

        void addFile(String &file);

        void removeFile(String &file);

    };
}