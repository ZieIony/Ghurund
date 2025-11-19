#pragma once

#include "MeshData.h"
#include "core/resource/Loader.h"

namespace Ghurund::Engine {
    class MeshDataLoader:public Loader {
    private:
        struct ObjVert {
            uint32_t posIndex, texCoordIndex, normalIndex, vertexIndex;
        };

        MeshData* loadObj(MemoryInputStream& stream);
        MeshData* loadMesh(MemoryInputStream& stream);

    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;
    };
}