#pragma once

#include "Mesh.h"
#include "core/resource/Loader.h"
#include "core/exception/Exceptions.h"

namespace Ghurund::Engine {
    class MeshLoader:public Loader {
    private:
        struct ObjVert {
            uint32_t posIndex, texCoordIndex, normalIndex, vertexIndex;
        };

        Mesh* loadObj(NotNull<MemoryInputStream> stream);
        Mesh* loadMesh(NotNull<MemoryInputStream> stream);

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