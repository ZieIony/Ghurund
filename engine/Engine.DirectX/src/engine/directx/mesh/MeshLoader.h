#pragma once

#include "DxMesh.h"

#include "core/resource/Loader.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class MeshLoader:public Loader {
    private:
        DxGPUMemoryManager& memoryManager;
        MeshDataLoader meshDataLoader;

    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            Ghurund::Core::LoadOption options
        ) override;

    public:
        MeshLoader(DxGPUMemoryManager& memoryManager):memoryManager(memoryManager) {}
    };
}