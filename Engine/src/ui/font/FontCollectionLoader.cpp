#include "FontCollectionLoader.h"
#include "FontFileEnumerator.h"

namespace Ghurund::UI {
    HRESULT STDMETHODCALLTYPE FontCollectionLoader::QueryInterface(REFIID iid, void** ppvObject) {
        if (iid == IID_IUnknown || iid == __uuidof(IDWriteFontCollectionLoader)) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        } else {
            *ppvObject = NULL;
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
        void const* collectionKey,                      // [collectionKeySize] in bytes
        UINT32 collectionKeySize,
        OUT IDWriteFontFileEnumerator** fontFileEnumerator
    ) {
        *fontFileEnumerator = NULL;

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
