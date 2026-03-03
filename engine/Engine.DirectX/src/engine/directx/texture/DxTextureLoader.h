#pragma once

#include "DxTexture.h"

#include "core/image/ImageLoader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxTextureLoader:public Loader {
    private:
        ImageLoader& imageLoader;
        DxGraphics& graphics;
		CommandList& commandList;

    protected:
        virtual DxTexture* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            auto image = IntrusivePointer((Image*)imageLoader.load(stream, workingDir, format, options));
            auto texture = makeIntrusive<DxTexture>();
            texture->init(graphics, commandList, image.ref(), TextureType::COLOR);
            texture->addReference();
            return texture.get();
        }

    public:
        DxTextureLoader(
            ImageLoader& imageLoader,
            DxGraphics& graphics,
            CommandList& commandList
        ):imageLoader(imageLoader), graphics(graphics), commandList(commandList) {}
    };
}
