#pragma once

#include "DxCubeMap.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxCubeMapLoader:public Loader<DxCubeMap> {
    private:
        ResourceManager& resourceManager;
        DxGPUMemoryManager& memoryManager;

        [[nodiscard]]
        CoroutineTask<IntrusivePointer<Image>> loadSide(const XMLElement& xml, const DirectoryPath& workingDir, WString side, uint32_t width, uint32_t height);

    protected:
        [[nodiscard]]
        virtual CoroutineTask<void> loadInternal(
            DxCubeMap& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

    public:
        DxCubeMapLoader(
            ResourceManager& resourceManager,
            DxGPUMemoryManager& memoryManager
        ):resourceManager(resourceManager), memoryManager(memoryManager) {}
    };
}
