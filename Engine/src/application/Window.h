#pragma once

#include "Ghurund.h"
#include "Settings.h"
#include "WindowProc.h"
#include "d3dx12.h"

namespace Ghurund {
    class Window {
    private:
        static const tchar *DEFAULT_WINDOW_TITLE;
        static const tchar *WINDOW_CLASS_NAME;

        tchar *title;
        WNDCLASSEX windowClass;
        HWND handle;
        HINSTANCE hInst;
        bool visible;
        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;
        unsigned int width, height;

    public:

        Window() = default;

        void init(HWND handle);
        void init(Settings &settings, WindowProc &windowProc);

        void uninit();

        /**
        * Ustawia tekst na pasku tytulu okna. Jesli podana zostanie wartosc null, ustawiony zostanie domyslny tytul 'Application'.
        * @param title tytul okna
        */
        inline void setTitle(const tchar *title) {
            safeCopyStr(&this->title, title);
            SetWindowText(handle, title ? title : DEFAULT_WINDOW_TITLE);
        }

        inline const tchar *getTitle() {
            return title;
        }

        __declspec(property(put = setTitle, get = getTitle)) tchar *Title;

        inline HWND getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        inline void setVisible(bool visible) {
            this->visible = visible;
            ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
        }

        inline bool isVisible() {
            return visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        D3D12_VIEWPORT &getViewport() {
            return viewport;
        }

        D3D12_RECT &getScissorRect() {
            return scissorRect;
        }

        inline unsigned int getWidth() {
            return width;
        }

        __declspec(property(get = getWidth)) unsigned int Width;

        inline unsigned int getHeight() {
            return height;
        }

        __declspec(property(get = getHeight)) unsigned int Height;
    };
}