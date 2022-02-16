#pragma once

#include "DragDropManager.h"
#include "Window.h"
#include "core/input/Input.h"
#include "core/window/WindowManager.h"
#include "WindowProc.h"

namespace Ghurund::Core {
    class WindowClass;

    class SystemWindow: public Window {
    private:
        HWND handle = {};
        Ghurund::Core::Input input;
        Ghurund::Core::Timer& timer;
        WindowData* windowData = nullptr;

        DragDropManager* dragDropManager = nullptr;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        Event<Ghurund::Core::Window> draggedOver = *this;
        Event<Ghurund::Core::Window> dragLeft = *this;
        Event<Ghurund::Core::Window, Array<FilePath*>&> dragEntered = *this;
        Event<Ghurund::Core::Window, Array<FilePath*>&> dropped = *this;

        SystemWindow(Ghurund::Core::Timer& timer):timer(timer) {}

        ~SystemWindow();

        virtual void init(WindowManager& windowManager);

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

        static const Ghurund::Core::Type& GET_TYPE();
    };
}