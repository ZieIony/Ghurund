#pragma once

#include "DxTexture.h"

#include "core/image/ImageLoader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxTextureLoader:public Loader<DxTexture> {
    private:
        ImageLoader& imageLoader;
        DxGraphics& graphics;
		CommandList& commandList;

    protected:
        virtual CoroutineTask<void> loadInternal(
            DxTexture& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            auto image = makeIntrusive<Image>();
            co_await imageLoader.load(image.ref(), stream, workingDir, format, options);
            resource.init(graphics, commandList, image.ref(), TextureType::COLOR);
        }

    public:
        DxTextureLoader(
            ImageLoader& imageLoader,
            DxGraphics& graphics,
            CommandList& commandList
        ):imageLoader(imageLoader), graphics(graphics), commandList(commandList) {}
    };
}
