#pragma once

#include "DragDropManager.h"
#include "Window.h"
#include "input/Input.h"

namespace Ghurund::UI {
    class RootView;
}

namespace Ghurund {
    class SystemWindow;
    class WindowClass;
    class SwapChain;

    struct WindowData {
        SystemWindow* window;
        bool mouseTracked = false;

        WindowData(SystemWindow* w):window(w) {}
    };

    LRESULT windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

    class SystemWindow: public Window {
    private:
        const WindowClass& windowClass;

        HWND handle;
        SwapChain* swapChain = nullptr;
        Ghurund::Input input;
        Ghurund::Timer& timer;
        Ghurund::UI::RootView* rootView = nullptr;

        DragDropManager* dragDropManager = nullptr;
        Event<Ghurund::Window> onDraggedOver = Event<Ghurund::Window>(*this);
        Event<Ghurund::Window> onDragLeft = Event<Ghurund::Window>(*this);
        Event<Ghurund::Window, Array<FilePath*>*> onDragEntered = Event<Ghurund::Window, Array<FilePath*>*>(*this);
        Event<Ghurund::Window, Array<FilePath*>*> onDropped = Event<Ghurund::Window, Array<FilePath*>*>(*this);

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SystemWindow))
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        SystemWindow(HWND handle, const WindowClass& type, Ghurund::Timer& timer);

        ~SystemWindow();

        inline const WindowClass& getClass() const {
            return windowClass;
        }

        __declspec(property(get = getClass)) const WindowClass& Class;

        virtual void setTitle(const WString& title) override {
            __super::setTitle(title);
            SetWindowTextW(handle, title);
        }

        virtual HWND getHandle() const override {
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

        virtual Ghurund::Input& getInput() override {
            return input;
        }

        __declspec(property(get = getInput)) Ghurund::Input& Input;

        virtual Ghurund::Timer& getTimer() const override {
            return timer;
        }

        __declspec(property(get = getTimer)) Ghurund::Timer& Timer;

        virtual void setVisible(bool visible) override {
            __super::setVisible(visible);
            ShowWindow(handle, visible ? SW_SHOWNOACTIVATE : SW_HIDE);
        }

        void setPosition(int x, int y);

        void setSize(unsigned int w, unsigned int h);

        virtual bool isFocused() const override {
            return handle == GetFocus();
        }

        void setDragDropEnabled(bool enabled);

        inline bool isDragDropEnabled() {
            return dragDropManager != nullptr;
        }

        __declspec(property(get = isDragDropEnabled, put = setDragDropEnabled)) bool DragDropEnabled;

        Event<Ghurund::Window>& getOnDraggedOver() {
            return onDraggedOver;
        }

        __declspec(property(get = getOnDraggedOver)) Event<Ghurund::Window>& OnDraggedOver;

        Event<Ghurund::Window>& getOnDragLeft() {
            return onDragLeft;
        }

        __declspec(property(get = getOnDragLeft)) Event<Ghurund::Window>& OnDragLeft;

        Event<Ghurund::Window, Array<FilePath*>*>& getOnDragEntered() {
            return onDragEntered;
        }

        __declspec(property(get = getOnDragEntered)) Event<Ghurund::Window, Array<FilePath*>*>& OnDragEntered;

        Event<Ghurund::Window, Array<FilePath*>*>& getOnDropped() {
            return onDropped;
        }

        __declspec(property(get = getOnDropped)) Event<Ghurund::Window, Array<FilePath*>*>& OnDropped;

        virtual void refresh() const override {
            RedrawWindow(handle, nullptr, nullptr, RDW_INVALIDATE);
        }

        virtual void activate() const override {
            SetActiveWindow(handle);
        }

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void onUpdate(const uint64_t time) override;

        virtual void onPaint();

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class OverlappedWindow:public SystemWindow {
    public:
        OverlappedWindow(Ghurund::Timer& timer);
    };

    class FullscreenWindow:public SystemWindow {
    public:
        FullscreenWindow(Ghurund::Timer& timer);
    };

    class PopupWindow:public SystemWindow {
    public:
        PopupWindow(Ghurund::Timer& timer);
    };
}