#pragma once

#include "Status.h"
#include "core/collection/List.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"

#include <dwrite.h>

namespace Ghurund::UI {
    class FontCollectionLoader: public IDWriteFontCollectionLoader {
    private:
        ULONG refCount = 0;
        List<UnicodeString> files;
        IDWriteFactory* dwriteFactory;

    public:
        FontCollectionLoader(IDWriteFactory* factory): dwriteFactory(factory) {}

        Status createFontCollection(const UnicodeString& fontFilePath, OUT IDWriteFontCollection** result) {
            *result = NULL;

            HRESULT hr = S_OK;

            UnicodeString absolutePath = FilePath(fontFilePath).AbsolutePath;
            size_t collectionKey = files.indexOf(absolutePath);
            if (collectionKey == files.Size) {
                files.add(absolutePath);
                collectionKey = files.Size - 1;
            }
            UINT32 keySize = sizeof(collectionKey);

            if (FAILED(dwriteFactory->CreateCustomFontCollection(this, &collectionKey, keySize, result)))
                return Status::CALL_FAIL;

            return Status::OK;
        }

        // IUnknown methods
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject);
        virtual ULONG STDMETHODCALLTYPE AddRef();
        virtual ULONG STDMETHODCALLTYPE Release();

        // IDWriteFontCollectionLoader methods
        virtual HRESULT STDMETHODCALLTYPE CreateEnumeratorFromKey(
            IDWriteFactory* factory,
            void const* collectionKey,
            UINT32 collectionKeySize,
            OUT IDWriteFontFileEnumerator** fontFileEnumerator
        );
    };
}
