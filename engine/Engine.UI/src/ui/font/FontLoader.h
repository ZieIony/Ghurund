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

        virtual Status load(Ghurund::ResourceManager& manager, MemoryInputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, LoadOption options = LoadOption::DEFAULT) override;

        virtual Status save(Ghurund::ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const override {
            return Status::NOT_IMPLEMENTED;
        }
    };
}