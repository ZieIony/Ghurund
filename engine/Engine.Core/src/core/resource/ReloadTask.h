#pragma once

#include "Resource.h"

namespace Ghurund::Core {
    class ReloadTask {
    private:
        ResourceManager& resourceManager;
        Loader& loader;
        Resource& resource;
        LoadOption loadOption;

    public:
        ReloadTask(ResourceManager& resourceManager, Loader& loader, Resource& resource, LoadOption loadOption)
            :resourceManager(resourceManager), loader(loader), resource(resource), loadOption(loadOption) {}

        Resource& getResource() {
            return resource;
        }

        __declspec(property(get = getResource)) Resource& Resource;

        void execute() {
            //loader.load(resourceManager, stream, resource, loadOption);
        }
    };
}
