#pragma once

#include "DragDropManager.h"
#include "Window.h"
#include "core/input/Input.h"

namespace Ghurund::Core {
    class WindowClass;

    LRESULT CALLBACK windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

    class SystemWindow: public Window {
    private:
        HWND handle;
        Ghurund::Core::Input input;
        Ghurund::Core::Timer& timer;

        DragDropManager* dragDropManager = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        Event<Ghurund::Core::Window> draggedOver = *this;
        Event<Ghurund::Core::Window> dragLeft = *this;
        Event<Ghurund::Core::Window, Array<FilePath*>&> dragEntered = *this;
        Event<Ghurund::Core::Window, Array<FilePath*>&> dropped = *this;

        SystemWindow(HWND handle, Ghurund::Core::Timer& timer);

        SystemWindow(const WindowClass& type, Ghurund::Core::Timer& timer);

        ~SystemWindow();

        virtual void setTitle(const WString& title) override {
            __super::setTitle(title);
            SetWindowTextW(handle, title.Data);
        }

        virtual HWND getHandle() const override {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        virtual Ghurund::Core::Input& getInput() override {
            return input;
        }

        __declspec(property(get = getInput)) Ghurund::Core::Input& Input;

        virtual Ghurund::Core::Timer& getTimer() const override {
            return timer;
        }

        __declspec(property(get = getTimer)) Ghurund::Core::Timer& Timer;

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

        virtual void refresh() const override {
            RedrawWindow(handle, nullptr, nullptr, RDW_INVALIDATE);
        }

        virtual void bringToFront() {
            SetWindowPos(handle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }

        virtual void sendToBack() {
            SetWindowPos(handle, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
        }

        virtual void update(const uint64_t time) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    struct WindowData {
        SystemWindow* window;
        bool mouseTracked = false;

        WindowData(SystemWindow* w):window(w) {}
    };
}