#include "ghuipch.h"
#include "FontLoader.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI {
    FontLoader::~FontLoader() {
        if (fontCollectionLoader) {
            factory.UnregisterFontCollectionLoader(fontCollectionLoader);
            fontCollectionLoader->Release();
            factory.UnregisterFontFileLoader(fontFileLoader);
            fontFileLoader->Release();
        }
    }

    Status FontLoader::init() {
        if (FAILED(factory.CreateInMemoryFontFileLoader(&fontFileLoader)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateInMemoryFontFileLoader failed\n"));
        if (FAILED(factory.RegisterFontFileLoader(fontFileLoader)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("RegisterFontFileLoader failed\n"));
        fontCollectionLoader = ghnew FontCollectionLoader(factory, *fontFileLoader);
        if (FAILED(factory.RegisterFontCollectionLoader(fontCollectionLoader)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("RegisterFontCollectionLoader failed\n"));
        return Status::OK;
    }

    Status FontLoader::load(ResourceManager& manager, MemoryInputStream& stream, Resource& resource, const ResourceFormat* format, LoadOption options) {
        Font& font = (Font&)resource;
        IDWriteFontCollection* collection = nullptr;
        if (FAILED(factory.CreateCustomFontCollection(fontCollectionLoader, stream.Data, (UINT32)stream.Size, &collection)))
            return Status::CALL_FAIL;
        font.init(collection);
        return Status::OK;
    }
}