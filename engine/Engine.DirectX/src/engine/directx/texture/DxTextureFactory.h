#pragma once

#include "DxTexture.h"
#include "engine/graphics/texture/ITextureFactory.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxTextureFactory:public ITextureFactory {
    private:
        DxGraphics& graphics;
        IntrusivePointer<CommandList> commandList;

    public:
        DxTextureFactory(DxGraphics& graphics, NotNull<CommandList> commandList):graphics(graphics), commandList(commandList.get()) {
            commandList->addReference();
        }

        virtual ITexture* makeTexture(Image& image, TextureType textureType) override {
            auto texture = ghnew DxTexture();
            texture->init(graphics, commandList.ref(), image, textureType);
            return texture;
        }
    };
}