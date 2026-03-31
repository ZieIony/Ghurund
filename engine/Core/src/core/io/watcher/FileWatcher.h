#pragma once

#include "core/string/String.h"
#include "core/threading/APCThread.h"
#include "DirectoryWatch.h"
#include "FileChange.h"
#include <core/Event.h>

namespace Ghurund::Core {
    class FileWatcher {
    private:
        APCThread thread;
        Map<WString, SharedPointer<DirectoryWatch>> watches;

        static void CALLBACK readChangesProc(__in  ULONG_PTR arg);

    public:
        Event<FileWatcher, const FileChange&> fileChanged = *this;

        FileWatcher();

        ~FileWatcher();

        inline bool containsFile(const FilePath& path) {
            WString dir = path.Directory.toString();
            return watches.contains(dir) && watches.get(dir)->containsFile(path);
        }

        void addFile(const FilePath& path);

        void removeFile(const FilePath& path);

        void clearFiles();
    };
}
