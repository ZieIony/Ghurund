#pragma once

#include "Status.h"
#include "core/collection/PointerList.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"
#include "ui/font/Font.h"

#include <dwrite_3.h>

namespace Ghurund::UI {
    class FontFileEnumerator: public IDWriteFontFileEnumerator {
    private:
        ULONG refCount = 1;
        void const* data;
        UINT32 size;
        IDWriteFontFile* currentFile = nullptr;
        size_t index = 0;
        IDWriteFactory& factory;
        IDWriteInMemoryFontFileLoader& fontFileLoader;

    public:
        FontFileEnumerator(IDWriteFactory& factory, IDWriteInMemoryFontFileLoader& fontFileLoader, void const* data, UINT32 size): factory(factory), fontFileLoader(fontFileLoader), data(data), size(size) {}

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject);
        virtual ULONG STDMETHODCALLTYPE AddRef();
        virtual ULONG STDMETHODCALLTYPE Release();

        virtual HRESULT STDMETHODCALLTYPE MoveNext(OUT BOOL* hasCurrentFile);
        virtual HRESULT STDMETHODCALLTYPE GetCurrentFontFile(OUT IDWriteFontFile** fontFile);
    };
}
