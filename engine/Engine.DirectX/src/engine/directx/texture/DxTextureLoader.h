#pragma once

#include "DxTexture.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxTextureLoader:public Loader<DxTexture> {
    private:
        ResourceManager& resourceManager;
        DxGPUMemoryManager& memoryManager;

    protected:
        virtual CoroutineTask<void> loadInternal(
            DxTexture& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

    public:
        DxTextureLoader(
            ResourceManager& resourceManager,
            DxGPUMemoryManager& memoryManager
        ):resourceManager(resourceManager), memoryManager(memoryManager) {}
    };
}
