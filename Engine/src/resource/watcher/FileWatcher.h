#pragma once

#include "Ghurund.h"
#include "core/FunctionQueue.h"
#include "collection/String.h"
#include "collection/List.h"
#include "DirectoryWatch.h"
#include "core/Thread.h"
#include "FileChange.h"

namespace Ghurund {
    class FileWatcher {
    private:
        APCThread thread;
        Map<UnicodeString, DirectoryWatch*> watches;

        static void CALLBACK readChangesProc(__in  ULONG_PTR arg);

    public:
        FileWatcher();

        ~FileWatcher();

        void addFile(const FilePath &path, std::function<void(const FilePath &path, const FileChange)> fileChangedHandler);

        void removeFile(const FilePath &path);

    };
}