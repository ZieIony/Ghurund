#include "FileWatcher.h"
#include "process.h"

namespace Ghurund {
    void FileWatcher::readChangesProc(ULONG_PTR arg) {
        DirectoryWatch* watch = (DirectoryWatch*)arg;
        watch->readChanges();
    }

    fs::path FileWatcher::getPath(const String &file) {
        int bufferLength = GetCurrentDirectory(0, nullptr)+file.Size+2; // slash and string terminator
        tchar *fullPath = ghnew tchar[bufferLength];
        GetFullPathName(file, bufferLength, fullPath, nullptr);
        auto path = fs::path(fullPath);
        delete[] fullPath;
        return path;
    }

    FileWatcher::FileWatcher() {
        thread.start();
    }

    FileWatcher::~FileWatcher() {
        for(size_t i = 0; i<watches.Size; i++)
            delete watches.getValue(i);
        thread.finish();
    }

    void FileWatcher::addFile(const String &file, std::function<void(const String &fileName, const FileChange)> fileChangedHandler) {
        auto path = getPath(file);
        String dir = path.parent_path().string().c_str();
        String fileName = path.filename().string().c_str();

        if(!watches.contains(dir)) {
            DirectoryWatch *watch = ghnew DirectoryWatch(dir);
            watches.set(dir, watch);

            watch->addFile(fileName, fileChangedHandler);

            thread.post(readChangesProc, (ULONG_PTR)watch);
        } else {
            watches[dir]->addFile(fileName, fileChangedHandler);
        }
    }

    void FileWatcher::removeFile(const String &file) {
        auto path = getPath(file);
        String dir = path.parent_path().string().c_str();
        String fileName = path.filename().string().c_str();

        if(!watches.contains(dir))
            return;

        DirectoryWatch *watch = watches[dir];
        watch->removeFile(fileName);
        if(watch->FileCount==0) {
            watches.remove(fileName);
            delete watch;
        }
    }
}