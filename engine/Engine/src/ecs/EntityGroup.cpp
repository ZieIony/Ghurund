#include "ghpch.h"
/*#include "Scene.h"

namespace Ghurund {
    Status EntityGroup::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        size_t size = stream.readUInt();
        for (size_t i = 0; i < size; i++) {
            Status result;
            Resource* resource = context.ResourceManager.load(context, workingDir, stream, &result, options);
            if (resource == nullptr)
                return result;
            entities.add((Entity*)resource);
            resource->release();
        }
        return Status::OK;
    }

    Status EntityGroup::saveInternal(ResourceContext & context, const DirectoryPath & workingDir, MemoryOutputStream & stream, SaveOption options) const {
        stream.writeUInt(entities.Size);
        for (size_t i = 0; i < entities.Size; i++) {
            Status result = context.ResourceManager.save(*entities[i], context, workingDir, stream, options);
            if (filterStatus(result, options) != Status::OK)
                return result;
        }
        return Status::OK;
    }
}*/