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

        Mesh* loadObj(MemoryInputStream& stream);
        Mesh* loadMesh(MemoryInputStream& stream);

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