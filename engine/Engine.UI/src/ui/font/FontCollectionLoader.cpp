#include "ghuipch.h"
#include "FontCollectionLoader.h"
#include "FontFileEnumerator.h"

#include "core/SharedPointer.h"

namespace Ghurund::UI {
    HRESULT STDMETHODCALLTYPE FontCollectionLoader::QueryInterface(REFIID iid, void** ppvObject) {
        if (iid == IID_IUnknown
            || iid == __uuidof(IDWriteFontCollectionLoader)) {
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
        *fontFileEnumerator = ghnew FontFileEnumerator(this->factory, fontFileLoader, collectionKey, collectionKeySize);
        return S_OK;
    }
}
