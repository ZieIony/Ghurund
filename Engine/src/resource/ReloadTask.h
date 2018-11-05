#pragma once

#include "Resource.h"

namespace Ghurund {
    class ResourceManager;

    class ReloadTask {
    private:
        ResourceManager &resourceManager;
        ResourceContext &context;
        Resource *resource;

    public:
        ReloadTask(ResourceManager &resourceManager, ResourceContext &context, Resource &resource):resourceManager(resourceManager), context(context) {
            this->resource = &resource;
        }

        Resource &getResource() {
            return *resource;
        }

        __declspec(property(get = getResource)) Resource &Resource;

        void execute() {
            resource->Valid = true;
            resource->invalidate();
            resource->addReference();
            resource->load(resourceManager, context);
            resource->release();
        }
    };
}