#pragma once

#include "Ghurund.h"
#include "core/FunctionQueue.h"
#include "collection/String.h"
#include "collection/List.h"
#include "DirectoryWatch.h"
#include "core/Thread.h"
#include "FileChange.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Ghurund {
    class FileWatcher {
    private:
        APCThread thread;
        Map<String, DirectoryWatch*> watches;

        static void CALLBACK readChangesProc(__in  ULONG_PTR arg);

        fs::path getPath(const String &file);

    public:
        FileWatcher();

        ~FileWatcher();

        void addFile(const String &fileName, std::function<void(const String &fileName, const FileChange)> fileChangedHandler);

        void removeFile(const String &fileName);

    };
}