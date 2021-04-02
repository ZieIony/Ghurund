#pragma once

#include "Resource.h"

namespace Ghurund {
    class ResourceManager;

    class ReloadTask {
    private:
        ResourceContext &context;
        Resource *resource;

    public:
        ReloadTask(ResourceContext &context, Resource &resource):context(context) {
            this->resource = &resource;
        }

        Resource &getResource() {
            return *resource;
        }

        __declspec(property(get = getResource)) Resource &Resource;

        void execute() {
            resource->reload(context);
        }
    };
}
