#pragma once

#include "Window.h"
#include "core/string/String.h"

namespace Ghurund {
    class Clipboard {
    private:
        Clipboard() = delete;

    public:
        static void putUnicodeText(HWND handle, const WString& data) {
            if (!OpenClipboard(handle))
                return;

            if (EmptyClipboard()) {
                HGLOBAL clipboardData = GlobalAlloc(GMEM_DDESHARE | GMEM_ZEROINIT, data.Size * sizeof(wchar_t));

                if (clipboardData) {
                    void* memory = GlobalLock(clipboardData);

                    if (memory) {
                        memcpy(memory, data.getData(), data.Size * sizeof(wchar_t));
                        GlobalUnlock(clipboardData);

                        if (SetClipboardData(CF_UNICODETEXT, clipboardData))
                            clipboardData = nullptr;
                    }
                    GlobalFree(clipboardData);
                }
            }
            CloseClipboard();
        }

        static WString* getUnicodeText(HWND handle) {
            UINT32 characterCount = 0;

            if (!OpenClipboard(handle))
                return nullptr;

            HGLOBAL clipboardData = GetClipboardData(CF_UNICODETEXT);
            WString* data = nullptr;

            if (clipboardData) {
                size_t byteSize = GlobalSize(clipboardData);
                const wchar_t* text = (wchar_t*)GlobalLock(clipboardData);

                if (text) {
                    data = ghnew WString(text);
                    GlobalUnlock(clipboardData);
                }
            }
            CloseClipboard();

            return data;
        }
    };
}