#include "FileWatcher.h"
#include "process.h"
#include "core/File.h"

namespace Ghurund {
    void FileWatcher::readChangesProc(ULONG_PTR arg) {
        DirectoryWatch* watch = (DirectoryWatch*)arg;
        watch->readChanges();
    }

    FileWatcher::FileWatcher() {
        thread.start();
    }

    FileWatcher::~FileWatcher() {
        for(size_t i = 0; i<watches.Size; i++)
            delete watches.getValue(i);
        thread.finish();
    }

    void FileWatcher::addFile(const FilePath &path, std::function<void(const FilePath &path, const FileChange)> fileChangedHandler) {
        String dir = path.Directory;

        if(!watches.contains(dir)) {
            DirectoryWatch *watch = ghnew DirectoryWatch(dir);
            watches.set(dir, watch);

            watch->addFile(path, fileChangedHandler);

            thread.post(readChangesProc, (ULONG_PTR)watch);
        } else {
            watches[dir]->addFile(path, fileChangedHandler);
        }
    }

    void FileWatcher::removeFile(const FilePath &path) {
        String dir = path.Directory;

        if(!watches.contains(dir))
            return;

        DirectoryWatch *watch = watches[dir];
        watch->removeFile(path);
        if(watch->FileCount==0) {
            watches.remove(path);
            delete watch;
        }
    }
}