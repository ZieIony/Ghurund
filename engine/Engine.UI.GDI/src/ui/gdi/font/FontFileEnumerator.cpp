#include "ghuigdipch.h"
#include "FontFileEnumerator.h"

#include <core/SharedPointer.h>

namespace Ghurund::UI {
    HRESULT STDMETHODCALLTYPE FontFileEnumerator::QueryInterface(REFIID iid, void** ppvObject) {
        if (iid == IID_IUnknown || iid == __uuidof(IDWriteFontFileEnumerator)) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        } else {
            *ppvObject = nullptr;
            return E_NOINTERFACE;
        }
    }

    ULONG STDMETHODCALLTYPE FontFileEnumerator::AddRef() {
        return InterlockedIncrement(&refCount);
    }

    ULONG STDMETHODCALLTYPE FontFileEnumerator::Release() {
        ULONG newCount = InterlockedDecrement(&refCount);
        if (newCount == 0)
            delete this;

        return newCount;
    }

    HRESULT STDMETHODCALLTYPE FontFileEnumerator::MoveNext(OUT BOOL* hasCurrentFile) {
        *hasCurrentFile = FALSE;
        if (currentFile) {
            currentFile->Release();
            currentFile = nullptr;
        }

        if (index != 0)
            return S_OK;

        HRESULT hr = fontFileLoader.CreateInMemoryFontFileReference(&factory, data, size, nullptr, &currentFile);

        if (FAILED(hr))
            return hr;

        *hasCurrentFile = TRUE;
        index++;

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE FontFileEnumerator::GetCurrentFontFile(OUT IDWriteFontFile** fontFile) {
        if (currentFile) {
            currentFile->AddRef();
            *fontFile = currentFile;
            return S_OK;
        } else {
            *fontFile = nullptr;
            return E_FAIL;
        }
    }
}
