#pragma once

#include "Status.h"
#include "core/collection/PointerList.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"
#include "ui/font/Font.h"

#include <dwrite_3.h>

namespace Ghurund::UI {
    class FontCollectionLoader: public IDWriteFontCollectionLoader {
    private:
        ULONG refCount = 1;
        IDWriteFactory5& factory;
        IDWriteInMemoryFontFileLoader& fontFileLoader;

    public:
        FontCollectionLoader(IDWriteFactory5& factory, IDWriteInMemoryFontFileLoader& fontFileLoader): factory(factory), fontFileLoader(fontFileLoader) {}

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject);
        virtual ULONG STDMETHODCALLTYPE AddRef();
        virtual ULONG STDMETHODCALLTYPE Release();

        virtual HRESULT STDMETHODCALLTYPE CreateEnumeratorFromKey(
            IDWriteFactory* factory,
            void const* collectionKey,
            UINT32 collectionKeySize,
            OUT IDWriteFontFileEnumerator** fontFileEnumerator
        ) override;
    };
}
