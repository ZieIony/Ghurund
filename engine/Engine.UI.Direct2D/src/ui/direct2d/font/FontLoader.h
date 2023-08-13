#pragma once

#include "core/resource/Loader.h"
#include "Font.h"
#include "ui/direct2d/font/FontCollectionLoader.h"
#include "core/Exceptions.h"

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class FontLoader:public Loader {
    private:
        IDWriteFactory5& factory;
        FontCollectionLoader* fontCollectionLoader = nullptr;
        IDWriteInMemoryFontFileLoader* fontFileLoader = nullptr;

    public:
        FontLoader(IDWriteFactory5& factory):factory(factory) {}

        ~FontLoader();

        void init();

        virtual Font* load(
            Ghurund::Core::ResourceManager& manager,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override;

        virtual void save(
            const Ghurund::Core::ResourceManager& manager,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override {
            throw NotImplementedException();
        }
    };
}