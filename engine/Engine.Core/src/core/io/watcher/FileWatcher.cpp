#include "ghcpch.h"
#include "FileWatcher.h"

#include "core/io/File.h"

#include <process.h>

namespace Ghurund::Core {
    void FileWatcher::readChangesProc(ULONG_PTR arg) {
        DirectoryWatch* watch = (DirectoryWatch*)arg;
        watch->readChanges();
    }

    FileWatcher::FileWatcher() {
        // TODO: fix thread finishing before it starts
        //thread.start();
    }

    FileWatcher::~FileWatcher() {
        while (!watches.Empty) {
            delete watches.begin()->value;
        }
        //thread.finish();
    }

    void FileWatcher::addFile(const FilePath& path, std::function<void(const FilePath& path, const FileChange&)> fileChangedHandler) {
        WString dir = path.Directory;

        if (!watches.contains(dir)) {
            DirectoryWatch* watch = ghnew DirectoryWatch(dir);
            watches.put(dir, watch);

            watch->addFile(path, fileChangedHandler);

            thread.post(readChangesProc, (ULONG_PTR)watch);
        } else {
            watches.get(dir)->addFile(path, fileChangedHandler);
        }
    }

    void FileWatcher::removeFile(const FilePath& path) {
        WString dir = path.Directory;

        if (!watches.contains(dir))
            return;

        DirectoryWatch* watch = watches.get(dir);
        watch->removeFile(path);
        if (watch->FileCount == 0) {
            watches.remove(dir);
            delete watch;
        }
    }
}