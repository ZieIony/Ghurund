#include "Scene.h"

namespace Ghurund {
    Status Scene::loadInternal(ResourceManager & resourceManager, ResourceContext & context, MemoryInputStream & stream, LoadOption options) {
        size_t size = stream.read<size_t>();
        for(size_t i = 0; i<size; i++) {
            Status result;
            Resource *resource = resourceManager.load(context, stream, &result, options);
            if(resource==nullptr)
                return result;
            entities.add((Entity*)resource);
            resource->release();
        }
        return Status::OK;
    }

    Status Scene::saveInternal(ResourceManager & resourceManager, MemoryOutputStream & stream, SaveOption options) const {
        stream.write(entities.Size);
        for(size_t i = 0; i<entities.Size; i++) {
            Status result = resourceManager.save(*entities[i], stream, options);
            if(filterStatus(result, options)!=Status::OK)
                return result;
        }
        return Status::OK;
    }
}