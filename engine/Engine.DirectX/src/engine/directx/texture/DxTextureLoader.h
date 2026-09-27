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
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override {
            // TODO: load image properly, so it can be cached
            auto image = co_await resourceManager.load<Image>(stream, workingDir, format, nullptr, { .cache = false });
            resource.init(image.ref(), memoryManager);
        }

    public:
        DxTextureLoader(
            ResourceManager& resourceManager,
            DxGPUMemoryManager& memoryManager
        ):resourceManager(resourceManager), memoryManager(memoryManager) {}
    };
}
