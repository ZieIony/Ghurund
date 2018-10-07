#include "ResourceManager.h"
#include <functional>
#include "TextResource.h"

namespace Ghurund {

    void ResourceManager::onFileChanged(const String &fileName, DWORD action) {
        Logger::log(_T("file changed: %s, action: %i\n"), fileName.getData(), action);
        switch(action) {
            case FILE_ACTION_ADDED:
                break;  // not possible
            case FILE_ACTION_REMOVED:
                //resources.remove<TextResource>(fileName);
                break;
            case FILE_ACTION_MODIFIED:
                //load<TextResource>(fileName);
                break;
            case FILE_ACTION_RENAMED_OLD_NAME:
                //resources.remove<TextResource>(fileName);   // tracking fileName changes not supported
                break;
            case FILE_ACTION_RENAMED_NEW_NAME:
                break;  // not supported
            default:
                break;  // not supported
        }
    }

    ResourceManager::ResourceManager() {
        std::function<void(const String&, DWORD)> changeListener = std::bind(&ResourceManager::onFileChanged, this, std::placeholders::_1, std::placeholders::_2);
        watcher = ghnew FileWatcher(changeListener);
        loadingThread.start();
    }

    ResourceManager::~ResourceManager() {
        loadingThread.finish();
        delete watcher;
        delete resourceFactory;
    }
}