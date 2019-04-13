#include "Scene.h"

namespace Ghurund {
    Status EntityGroup::loadInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        size_t size = stream.read<size_t>();
        for (size_t i = 0; i < size; i++) {
            Status result;
            Resource* resource = resourceManager.load(context, workingDir, stream, &result, options);
            if (resource == nullptr)
                return result;
            entities.add((Entity*)resource);
            resource->release();
        }
        return Status::OK;
    }

    Status EntityGroup::saveInternal(ResourceManager & resourceManager, ResourceContext & context, const DirectoryPath & workingDir, MemoryOutputStream & stream, SaveOption options) const {
        stream.write(entities.Size);
        for (size_t i = 0; i < entities.Size; i++) {
            Status result = resourceManager.save(*entities[i], context, workingDir, stream, options);
            if (filterStatus(result, options) != Status::OK)
                return result;
        }
        return Status::OK;
    }
}