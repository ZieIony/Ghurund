#include "ghuidxpch.h"
#include "FontLoader.h"

#include "core/Exceptions.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI::Direct2D {
    FontLoader::~FontLoader() {
        if (fontCollectionLoader) {
            factory.UnregisterFontCollectionLoader(fontCollectionLoader);
            fontCollectionLoader->Release();
            factory.UnregisterFontFileLoader(fontFileLoader);
            fontFileLoader->Release();
        }
    }

    void FontLoader::init() {
        if (FAILED(factory.CreateInMemoryFontFileLoader(&fontFileLoader))) {
            Logger::log(LogType::ERR0R, _T("CreateInMemoryFontFileLoader failed\n"));
            throw CallFailedException();
        }
        if (FAILED(factory.RegisterFontFileLoader(fontFileLoader))) {
            Logger::log(LogType::ERR0R, _T("RegisterFontFileLoader failed\n"));
            throw CallFailedException();
        }
        fontCollectionLoader = ghnew FontCollectionLoader(factory, *fontFileLoader);
        if (FAILED(factory.RegisterFontCollectionLoader(fontCollectionLoader))) {
            Logger::log(LogType::ERR0R, _T("RegisterFontCollectionLoader failed\n"));
            throw CallFailedException();
        }
    }

    Font* FontLoader::load(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat* format,
        LoadOption options
    ) {
        Microsoft::WRL::ComPtr<IDWriteFontCollection> collection;
        if (FAILED(factory.CreateCustomFontCollection(fontCollectionLoader, stream.Data, (UINT32)stream.Size, &collection)))
            throw CallFailedException();
        Font* font = makeResource<Ghurund::UI::Direct2D::Font>();
        font->init(collection.Get());
        return font;
    }
}