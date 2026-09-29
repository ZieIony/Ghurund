#pragma once

#include "DxCubeMap.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxCubeMapLoader:public Loader<DxCubeMap> {
    private:
        ResourceManager& resourceManager;
        DxGPUMemoryManager& memoryManager;

        [[nodiscard]]
        CoroutineTask<List<IntrusivePointer<Image>>> loadFace(
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            WString side,
            IntSize size,
            const ResourceFormat& format,
            LoadOptions options
        );

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
