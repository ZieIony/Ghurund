#pragma once

#include "DragDropManager.h"
#include "Window.h"
#include "input/Input.h"
#include "LayerList.h"

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
        Input::Input input;
        Ghurund::Timer& timer;
        LayerList layers;

        DragDropManager* dragDropManager = nullptr;
        Event<Ghurund::Window> onDraggedOver = Event<Ghurund::Window>(*this);
        Event<Ghurund::Window> onDragLeft = Event<Ghurund::Window>(*this);
        Event<Ghurund::Window, Array<FilePath*>*> onDragEntered = Event<Ghurund::Window, Array<FilePath*>*>(*this);
        Event<Ghurund::Window, Array<FilePath*>*> onDropped = Event<Ghurund::Window, Array<FilePath*>*>(*this);

    protected:
        virtual bool onSizeChangedEvent() override {
            layers.Size = Size;
            return true;
        }

        virtual bool onFocusedChangedEvent() override {
            if (Focused) {
                layers.restoreFocus();
            } else {
                layers.clearFocus();
            }
            return true;
        }

        static const Ghurund::Type& GET_TYPE();

    public:
        SystemWindow(const WindowClass& type, Ghurund::Timer& timer);

        ~SystemWindow();

        inline const WindowClass& getClass() const {
            return windowClass;
        }

        __declspec(property(get = getClass)) const WindowClass& Class;

        virtual void setTitle(const WString& title) override {
            __super::setTitle(title);
            SetWindowTextW(handle, title.Data);
        }

        virtual HWND getHandle() const override {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        inline LayerList &getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList& Layers;

        inline SwapChain* getSwapChain() {
            return swapChain;
        }

        inline void setSwapChain(SwapChain* swapChain) {
            this->swapChain = swapChain;
        }

        __declspec(property(get = getSwapChain, put = setSwapChain)) SwapChain* SwapChain;

        virtual Input::Input& getInput() override {
            return input;
        }

        __declspec(property(get = getInput)) Input::Input& Input;

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

        virtual void activate() override {
            Visible = true;
            SetActiveWindow(handle);
        }

        virtual bool onKeyEvent(const Input::KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const Input::MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const Input::MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const Input::MouseWheelEventArgs& args) override;

        virtual void onUpdate(const uint64_t time) override;

        virtual Status onPaint() override {
            return layers.draw();
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}