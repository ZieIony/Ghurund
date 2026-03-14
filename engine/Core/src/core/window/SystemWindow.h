#pragma once

#include "DragDropManager.h"
#include "Window.h"
#include "WindowClass.h"
#include "WindowDecorationMetrics.h"
#include "core/object/NotNull.h"
#include "core/object/SharedPointer.h"
#include "core/collection/Map.h"
#include "core/input/Input.h"

#include <wrl/client.h>
#include <memory>

namespace Ghurund::Core {
    class SystemWindow:public Window {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = SystemWindow::GET_TYPE();
#pragma endregion
    private:
        static inline Map<SharedPointer<WindowClass>, uint32_t> windowClassUses;
        SharedPointer<WindowClass> windowClass;

        WindowStyle style;
        
        HWND handle = {};
        Ghurund::Core::Input input;
        Ghurund::Core::Timer& timer;
        bool mouseTracked = false;

        Microsoft::WRL::ComPtr<DragDropManager> dragDropManager;
        WindowDecorationMetrics decorationMetrics;

        HWND makeWindow();

        void destroyWindow();

        void applyVisible();
        void applyPosition();
        void applySize();
        void applyTitle();

    protected:
        static const inline WindowStyle DEFAULT_WINDOW_STYLE = {
            .hasMinimizeButton = true,
            .hasMaximizeButton = true,
            .hasTitle = true,
            .borderStyle = WindowBorderStyle::RESIZE,
            .showOnTaskbar = true
        };

        virtual bool onPositionChanged() override;

        virtual bool onSizeChanged() override;

        virtual bool onFocusedChanged() override {
            __super::onFocusedChanged();
            input.releaseAllKeysAndButtons();
            return true;
        }

    public:
        Event<Ghurund::Core::Window> draggedOver = *this;
        Event<Ghurund::Core::Window> dragLeft = *this;
        Event<Ghurund::Core::Window, Array<FilePath*>&> dragEntered = *this;
        Event<Ghurund::Core::Window, Array<FilePath*>&> dropped = *this;

        SystemWindow(Ghurund::Core::Timer& timer, WindowStyle style = DEFAULT_WINDOW_STYLE);

        ~SystemWindow();

        inline WindowStyle getStyle() const {
            return style;
        }

        void setStyle(WindowStyle style);

        __declspec(property(get = getStyle, put = setStyle)) WindowStyle Style;

        virtual HWND getHandle() const override {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        virtual void setClientPosition(const XMINT2& pos) override {
            setPosition(pos.x - DecorationMetrics.Left, pos.y - DecorationMetrics.Top);
        }

        virtual XMINT2 getClientPosition() override {
            return { Position.x + (int32_t)DecorationMetrics.Left, Position.y + (int32_t)DecorationMetrics.Top };
        }

        virtual void setClientSize(const IntSize& size) override {
            setSize(size.Width + DecorationMetrics.Horizontal, size.Height + DecorationMetrics.Vertical);
        }

        virtual IntSize getClientSize() override {
            return { Size.Width - DecorationMetrics.Horizontal, Size.Height - DecorationMetrics.Vertical };
        }

        virtual Ghurund::Core::Input* getInput() override {
            return &input;
        }

        __declspec(property(get = getInput)) Ghurund::Core::Input* Input;

        virtual Ghurund::Core::Timer& getTimer() const override {
            return timer;
        }

        __declspec(property(get = getTimer)) Ghurund::Core::Timer& Timer;

        inline const WindowDecorationMetrics& getDecorationMetrics() const {
            return decorationMetrics;
        }

        __declspec(property(get = getDecorationMetrics)) WindowDecorationMetrics& DecorationMetrics;

        virtual void setVisible(bool visible) override;

        virtual void setTitle(const String& title) override;

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

        void dispatchInputEvents();

        void dispatchMouseEvent(UINT msg, WPARAM wParam, LPARAM lParam);

        bool dispatchWindowEvent(UINT msg, WPARAM wParam, LPARAM lParam);

        inline void minimize() {
            CloseWindow(handle);
        }
    };
}
