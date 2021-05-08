#pragma once

#include "core/resource/Loader.h"
#include "ui/font/Font.h"
#include "ui/font/FontCollectionLoader.h"

namespace Ghurund::UI {
    class FontLoader:public Loader {
    private:
        IDWriteFactory5& factory;
        FontCollectionLoader* fontCollectionLoader = nullptr;
        IDWriteInMemoryFontFileLoader* fontFileLoader = nullptr;

    public:
        FontLoader(IDWriteFactory5& factory):factory(factory) {}

        ~FontLoader();

        Status init();

        virtual Status load(ResourceManager& manager, MemoryInputStream& stream, Resource& resource, LoadOption options) override;

        virtual Status save(ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, SaveOption options) const override {
            return Status::NOT_IMPLEMENTED;
        }
    };
}