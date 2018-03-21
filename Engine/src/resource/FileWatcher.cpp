#include "FileWatcher.h"
#include "process.h"

namespace Ghurund {
    void FileWatcher::readChangesProc(ULONG_PTR arg) {
        DirectoryWatch* watch = (DirectoryWatch*)arg;
        watch->readChanges();
    }

    void FileWatcher::getFullPathName(tchar ** fullDir, const tchar * file) {
        int bufferLength = GetCurrentDirectory(0, nullptr)+_tcslen(file)+2; // slash and string terminator
        tchar *filePart;
        *fullDir = ghnew tchar[bufferLength];
        GetFullPathName(file, bufferLength, *fullDir, &filePart);
        filePart[0] = 0;
    }

    DirectoryWatch * FileWatcher::findWatch(const tchar * fullPath) {
        for(size_t i = 0; i<watches.Size; i++)
            if(_tcscmp(fullPath, watches[i]->getDirectory())==0)
                return watches[i];
        return nullptr;
    }

    void FileWatcher::getFullPath(tchar ** fullPath, const tchar * file) {
        int bufferLength = GetCurrentDirectory(0, nullptr)+_tcslen(file)+2; // slash and string terminator
        tchar *filePart;
        *fullPath = ghnew tchar[bufferLength];
        GetFullPathName(file, bufferLength, *fullPath, &filePart);
        filePart[0] = 0;
    }

    FileWatcher::FileWatcher(std::function<void(const String&, DWORD)> fileChangedHandler):fileChangedHandler(fileChangedHandler) {
        thread.start();
    }

    FileWatcher::~FileWatcher() {
        for(size_t i = 0; i<watches.Size; i++)
            delete[] watches[i];
        thread.finish();
    }

    void FileWatcher::addFile(String &file) {
        tchar *fullPath;
        getFullPath(&fullPath, file.getData());
        DirectoryWatch *watch = findWatch(fullPath);

        if(watch==nullptr) {
            watch = ghnew DirectoryWatch(fullPath, fileChangedHandler);
            watches.add(watch);
        }
        watch->addFile(file);
        thread.post(readChangesProc, (ULONG_PTR)watch);

        delete[] fullPath;
    }

    void FileWatcher::removeFile(String &file) {
        tchar *fullPath;
        getFullPath(&fullPath, file.getData());
        DirectoryWatch *watch = findWatch(fullPath);

        if(watch==nullptr)
            return;

        watch->removeFile(file);
        if(watch->getFileCount()==0) {
            watches.remove(watch);
            delete watch;
        }
    }
}