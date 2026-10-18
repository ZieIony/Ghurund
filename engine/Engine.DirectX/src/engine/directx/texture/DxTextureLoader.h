#pragma once

#include "DxTexture.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxTextureLoader:public Loader<DxTexture> {
    private:
        ResourceManager& resourceManager;
        DxGPUMemoryManager& memoryManager;

    protected:
        virtual CoroutineTask<void> load_internal(
            DxTexture& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        [[nodiscard]]
        virtual CoroutineTask<void> init_internal(DxTexture& resource) {
            resource.init(memoryManager);
            co_return;
        }

        [[nodiscard]]
        virtual CoroutineTask<void> deinit_internal(DxTexture& resource) {
            resource.deinit();
            co_return;
        }

        [[nodiscard]]
        virtual CoroutineTask<void> unload_internal(DxTexture& resource) {
            resource.unload();
            co_return;
        }

    public:
        DxTextureLoader(
            ResourceManager& resourceManager,
            DxGPUMemoryManager& memoryManager
        ):resourceManager(resourceManager), memoryManager(memoryManager) {}

        static CoroutineTask<List<IntrusivePointer<Image>>> loadMipImages(
            ResourceManager& resourceManager,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        );
    };
}
