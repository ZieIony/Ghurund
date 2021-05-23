#pragma once

#include "DragDropManager.h"
#include "Window.h"
#include "core/input/Input.h"

namespace Ghurund {
    class SystemWindow;
    class WindowClass;
    class SwapChain;

    struct WindowData {
        SystemWindow* window;
        bool mouseTracked = false;

        WindowData(SystemWindow* w):window(w) {}
    };

    LRESULT CALLBACK windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

    class SystemWindow: public Window {
    private:
        const WindowClass& windowClass;

        HWND handle;
        Ghurund::Input input;
        Ghurund::Timer& timer;

        DragDropManager* dragDropManager = nullptr;
        Event<Ghurund::Window> onDraggedOver = Event<Ghurund::Window>(*this);
        Event<Ghurund::Window> onDragLeft = Event<Ghurund::Window>(*this);
        Event<Ghurund::Window, Array<FilePath*>&> onDragEntered = Event<Ghurund::Window, Array<FilePath*>&>(*this);
        Event<Ghurund::Window, Array<FilePath*>&> onDropped = Event<Ghurund::Window, Array<FilePath*>&>(*this);

    protected:
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

        Event<Ghurund::Window, Array<FilePath*>&>& getOnDragEntered() {
            return onDragEntered;
        }

        __declspec(property(get = getOnDragEntered)) Event<Ghurund::Window, Array<FilePath*>&>& OnDragEntered;

        Event<Ghurund::Window, Array<FilePath*>&>& getOnDropped() {
            return onDropped;
        }

        __declspec(property(get = getOnDropped)) Event<Ghurund::Window, Array<FilePath*>&>& OnDropped;

        virtual void refresh() const override {
            RedrawWindow(handle, nullptr, nullptr, RDW_INVALIDATE);
        }

        virtual void activate() override {
            Visible = true;
            SetActiveWindow(handle);
        }

        virtual void update(const uint64_t time) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}