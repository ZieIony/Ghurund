#pragma once

#include "MeshData.h"

#include "core/loading/Loader.h"

namespace Ghurund::Engine {
    class MeshDataLoader:public Loader<MeshData> {
    private:
        struct ObjVert {
            uint32_t posIndex, texCoordIndex, normalIndex, vertexIndex;
        };

        void loadObj(MeshData& mesh, MemoryInputStream& stream);
        void loadMesh(MeshData& mesh, MemoryInputStream& stream);

    protected:
        virtual void loadInternal(
            MeshData& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            MeshData& resource,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            SaveOption options
        ) const override;
    };
}