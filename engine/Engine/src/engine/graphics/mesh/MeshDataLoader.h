#pragma once

#include "MeshData.h"

#include "core/loading/Loader.h"

namespace Ghurund::Engine {
    class MeshDataLoader:public Loader<MeshData> {
    private:
        void loadAssimp(MeshData& mesh, MemoryInputStream& stream);
        void loadMesh(MeshData& mesh, MemoryInputStream& stream);

        void saveMesh(MeshData& resource, MemoryOutputStream& stream) const;

    protected:
        virtual const ResourceFormat& getPreferredSaveFormat() const override {
            return MeshData::FORMAT_MESH;
        }

    protected:
        [[nodiscard]]
        virtual CoroutineTask<void> loadInternal(
            MeshData& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        virtual void saveInternal(
            MeshData& resource,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            SaveOptions options
        ) const override;
    };
}
