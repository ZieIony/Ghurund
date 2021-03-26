#include "ghuipch.h"
#include "FontCollectionLoader.h"

#include "FontFileEnumerator.h"

namespace Ghurund::UI {
    Status FontCollectionLoader::createFontCollection(const WString& fontFilePath, OUT IDWriteFontCollection** result) {
        *result = nullptr;

        WString absolutePath = FilePath(fontFilePath).AbsolutePath;
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
    
    HRESULT STDMETHODCALLTYPE FontCollectionLoader::QueryInterface(REFIID iid, void** ppvObject) {
        if (iid == IID_IUnknown || iid == __uuidof(IDWriteFontCollectionLoader)) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        } else {
            *ppvObject = nullptr;
            return E_NOINTERFACE;
        }
    }

    ULONG STDMETHODCALLTYPE FontCollectionLoader::AddRef() {
        return InterlockedIncrement(&refCount);
    }

    ULONG STDMETHODCALLTYPE FontCollectionLoader::Release() {
        ULONG newCount = InterlockedDecrement(&refCount);
        if (newCount == 0)
            delete this;

        return newCount;
    }

    HRESULT STDMETHODCALLTYPE FontCollectionLoader::CreateEnumeratorFromKey(
        IDWriteFactory* factory,
        void const* collectionKey,
        UINT32 collectionKeySize,
        OUT IDWriteFontFileEnumerator** fontFileEnumerator
    ) {
        *fontFileEnumerator = nullptr;

        if (collectionKeySize % sizeof(UINT) != 0)
            return E_INVALIDARG;

        size_t const* mfCollectionKey = (size_t const*)collectionKey;
        UINT32 const mfKeySize = collectionKeySize;

        FontFileEnumerator* enumerator = new(std::nothrow) FontFileEnumerator(factory, files[*mfCollectionKey]);
        if (!enumerator)
            return E_OUTOFMEMORY;

        *fontFileEnumerator = enumerator;

        return S_OK;
    }
}
