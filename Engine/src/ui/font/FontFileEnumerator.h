#pragma once

#include "core/string/String.h"

#include <dwrite.h>

namespace Ghurund::UI {
    class FontFileEnumerator: public IDWriteFontFileEnumerator {
    private:
        ULONG refCount = 0;

        IDWriteFactory* dwriteFactory = nullptr;
        IDWriteFontFile* currentFile = nullptr;
        UnicodeString fontFilePath;
        size_t nextIndex = 0;

    public:
        FontFileEnumerator(IDWriteFactory* factory, const UnicodeString& fontFilePath);

        ~FontFileEnumerator() {
            if (currentFile)
                currentFile->Release();
            if (dwriteFactory)
                dwriteFactory->Release();
        }

        // IUnknown methods
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject);
        virtual ULONG STDMETHODCALLTYPE AddRef();
        virtual ULONG STDMETHODCALLTYPE Release();

        // IDWriteFontFileEnumerator methods
        virtual HRESULT STDMETHODCALLTYPE MoveNext(OUT BOOL* hasCurrentFile);
        virtual HRESULT STDMETHODCALLTYPE GetCurrentFontFile(OUT IDWriteFontFile** fontFile);
    };
}
