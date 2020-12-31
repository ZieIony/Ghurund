#pragma once

#include "DirectoryWatch.h"
#include "FileChange.h"
#include "core/string/String.h"
#include "core/collection/List.h"
#include "core/threading/FunctionQueue.h"
#include "core/threading/Thread.h"

namespace Ghurund {
    class FileWatcher {
    private:
        APCThread thread;
        Map<WString, DirectoryWatch*> watches;

        static void CALLBACK readChangesProc(__in  ULONG_PTR arg);

    public:
        FileWatcher();

        ~FileWatcher();

        void addFile(const FilePath& path, std::function<void(const FilePath& path, const FileChange&)> fileChangedHandler);

        void removeFile(const FilePath& path);

    };
}