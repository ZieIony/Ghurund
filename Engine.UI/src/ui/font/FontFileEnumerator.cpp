#include "ghuipch.h"
#include "FontFileEnumerator.h"

namespace Ghurund::UI {
    FontFileEnumerator::FontFileEnumerator(IDWriteFactory* factory, const WString& fontFilePath):fontFilePath(fontFilePath) {
        if (factory) {
            factory->AddRef();
            dwriteFactory = factory;
        }
    }

    HRESULT STDMETHODCALLTYPE FontFileEnumerator::QueryInterface(REFIID iid, void** ppvObject) {
        if (iid == IID_IUnknown || iid == __uuidof(IDWriteFontFileEnumerator)) {
            *ppvObject = this;
            AddRef();
            return S_OK;
        } else {
            *ppvObject = NULL;
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

        if (nextIndex == 0) {
            HRESULT hr = dwriteFactory->CreateFontFileReference(fontFilePath.getData(), NULL, &currentFile);

            if (SUCCEEDED(hr)) {
                *hasCurrentFile = TRUE;
                nextIndex++;
            }

            return hr;
        }

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