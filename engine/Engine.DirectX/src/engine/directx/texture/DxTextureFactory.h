#pragma once

#include "DxTexture.h"
#include "engine/graphics/texture/ITextureFactory.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxTextureFactory:public ITextureFactory {
    private:
        DxGraphics& graphics;
        CommandList& commandList;

    public:
        DxTextureFactory(DxGraphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}

        virtual ITexture* makeTexture(Image& image) override {
            auto texture = ghnew DxTexture();
            texture->init(graphics, commandList, image);
            return texture;
        }
    };
}