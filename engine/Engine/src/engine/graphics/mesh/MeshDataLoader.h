#pragma once

#include "MeshData.h"
#include "core/resource/Loader.h"
#include "core/exception/Exceptions.h"

namespace Ghurund::Engine {
    class MeshDataLoader:public Loader {
    private:
        struct ObjVert {
            uint32_t posIndex, texCoordIndex, normalIndex, vertexIndex;
        };

        MeshData* loadObj(NotNull<MemoryInputStream> stream);
        MeshData* loadMesh(NotNull<MemoryInputStream> stream);

    protected:
        virtual Resource* loadInternal(
            NotNull<MemoryInputStream> stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            NotNull<MemoryOutputStream> stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;
    };
}