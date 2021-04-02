#pragma once

#include "Status.h"
#include "core/collection/List.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"

#include <dwrite.h>

namespace Ghurund::UI {
    class FontCollectionLoader: public IDWriteFontCollectionLoader {
    private:
        ULONG refCount = 1;
        List<WString> files;
        IDWriteFactory* dwriteFactory;

    public:
        FontCollectionLoader(IDWriteFactory* factory): dwriteFactory(factory) {}

        Status createFontCollection(const WString& fontFilePath, OUT IDWriteFontCollection** result);

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject);
        virtual ULONG STDMETHODCALLTYPE AddRef();
        virtual ULONG STDMETHODCALLTYPE Release();

        virtual HRESULT STDMETHODCALLTYPE CreateEnumeratorFromKey(
            IDWriteFactory* factory,
            void const* collectionKey,
            UINT32 collectionKeySize,
            OUT IDWriteFontFileEnumerator** fontFileEnumerator
        );
    };
}
