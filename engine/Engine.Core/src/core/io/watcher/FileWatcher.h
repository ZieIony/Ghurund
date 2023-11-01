#pragma once

#include "DirectoryWatch.h"
#include "FileChange.h"
#include "core/string/String.h"
#include "core/collection/List.h"
#include "core/threading/FunctionQueue.h"
#include "core/threading/APCThread.h"

namespace Ghurund::Core {
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

        void clearFiles() {
            while (!watches.Empty) {
                auto& key = watches.begin()->key;
                DirectoryWatch* watch = watches.get(key);
                watches.remove(key);
                delete watch;
            }
        }
    };
}