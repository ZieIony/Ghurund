#pragma once

#include "Window.h"
#include "ui/RootView.h"

namespace Ghurund {
    struct WindowMessage {
        unsigned int code;
        WPARAM wParam;
        LPARAM lParam;
        time_t time;
    };

    class SystemWindow;
    class WindowClass;
    class SwapChain;

    struct WindowData {
        SystemWindow* window;
        POINT prevMousePos = { -1,-1 };
        bool mouseTracked = false;

        WindowData(SystemWindow* w):window(w) {}
    };

    LRESULT windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

    class SystemWindow: public Window {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(SystemWindow);

        const WindowClass& windowClass;

        HWND handle;
        SwapChain* swapChain = nullptr;
        Ghurund::UI::RootView* rootView = nullptr;

        EventHandler<Ghurund::Window> onSizeChangedHandler;

    public:
        SystemWindow(HWND handle, const WindowClass& type);

        ~SystemWindow();

        inline const WindowClass& getClass() const {
            return windowClass;
        }

        __declspec(property(get = getClass)) const WindowClass& Class;

        virtual void setTitle(const String& title) override {
            __super::setTitle(title);
            SetWindowText(handle, title);
        }

        inline HWND getHandle() const {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        inline Ghurund::UI::RootView* getRootView() {
            return rootView;
        }

        void setRootView(Ghurund::UI::RootView* rootView);

        __declspec(property(get = getRootView, put = setRootView)) Ghurund::UI::RootView* RootView;

        inline SwapChain* getSwapChain() {
            return swapChain;
        }

        inline void setSwapChain(SwapChain* swapChain) {
            this->swapChain = swapChain;
        }

        __declspec(property(get = getSwapChain, put = setSwapChain)) SwapChain* SwapChain;

        virtual void setVisible(bool visible) override {
            __super::setVisible(visible);
            ShowWindow(handle, visible ? SW_SHOWNOACTIVATE : SW_HIDE);
        }

        void setPosition(int x, int y);

        void setSize(unsigned int w, unsigned int h);

        virtual bool isFocused() const override {
            return handle == GetFocus();
        }

        virtual void refresh() const override {
            RedrawWindow(handle, nullptr, nullptr, RDW_INVALIDATE);
        }

        virtual void activate() const override {
            SetActiveWindow(handle);
        }
        
        inline static const Ghurund::Type& TYPE = TypeBuilder<SystemWindow>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class OverlappedWindow:public SystemWindow {
    public:
        OverlappedWindow();
    };

    class FullscreenWindow:public SystemWindow {
    public:
        FullscreenWindow();
    };

    class PopupWindow:public SystemWindow {
    public:
        PopupWindow();
    };
}