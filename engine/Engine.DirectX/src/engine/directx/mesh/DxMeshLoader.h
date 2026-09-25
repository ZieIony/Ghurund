#pragma once

#include "DxMesh.h"

#include "core/loading/Loader.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxMeshLoader:public Loader<DxMesh> {
    private:
        DxGPUMemoryManager& memoryManager;
        IntrusivePointer<MeshDataLoader> meshDataLoader;

    protected:
        virtual CoroutineTask<void> loadInternal(
            DxMesh& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

    public:
        DxMeshLoader(
            DxGPUMemoryManager& memoryManager
		):memoryManager(memoryManager), meshDataLoader(makeIntrusive<MeshDataLoader>()) {
		}
    };
}
