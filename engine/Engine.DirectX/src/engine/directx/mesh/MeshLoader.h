#pragma once

#include "DxMesh.h"

#include "core/loading/Loader.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class MeshLoader:public Loader<DxMesh> {
    private:
        DxGPUMemoryManager& memoryManager;
        MeshDataLoader meshDataLoader;

    protected:
        virtual void loadInternal(
            DxMesh& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

    public:
        MeshLoader(DxGPUMemoryManager& memoryManager):memoryManager(memoryManager) {}
    };
}