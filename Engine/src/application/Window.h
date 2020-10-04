#pragma once

#include "application/Settings.h"
#include "core/Event.h"
#include "core/NamedObject.h"
#include "core/Object.h"
#include "core/collection/Array.h"
#include "core/threading/FunctionQueue.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ValueParameter.h"
#include "graphics/Graphics.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

#pragma warning(push, 0)
#include "d3dx12.h"
#pragma warning(pop)

namespace Ghurund {
    struct WindowMessage {
        unsigned int code;
        WPARAM wParam;
        LPARAM lParam;
        time_t time;
    };

    struct WindowSizeChangedEventArgs {
        unsigned int width, height;
    };

    class Window;
    class WindowClass;

    struct WindowData {
        Window* window;
        POINT prevMousePos = { -1,-1 };

        WindowData(Window* w):window(w) {}
    };

    LRESULT windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

    class Window: public ParameterProvider, public NamedObject<String>, public Object {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Window);

        const WindowClass& windowClass;

        String title;
        HWND handle;
        bool visible;
        POINT position;
        XMINT2 size;

        PointerArray<Parameter*> parameters;
        ValueParameter* parameterViewportSize = nullptr;

        Event<Window> onCreated = Event<Window>(*this);
        Event<Window> onPositionChanged = Event<Window>(*this);
        Event<Window> onSizeChanged = Event<Window>(*this);
        Event<Window> onPaint = Event<Window>(*this);
        Event<Window> onDestroy = Event<Window>(*this);

        Event<Window, KeyEventArgs> onKeyEvent = Event<Window, KeyEventArgs>(*this);
        Event<Window, MouseButtonEventArgs> onMouseButtonEvent = Event<Window, MouseButtonEventArgs>(*this);
        POINT prevMousePos = { -1, -1 };
        Event<Window, MouseMotionEventArgs> onMouseMotionEvent = Event<Window, MouseMotionEventArgs>(*this);
        Event<Window, MouseWheelEventArgs> onMouseWheelEvent = Event<Window, MouseWheelEventArgs>(*this);

        FunctionQueue* functionQueue = nullptr;

    public:
        Window(HWND handle, const WindowClass& type);

        ~Window();

        virtual void initParameters(ParameterManager& parameterManager) override {
            if (parameterViewportSize != nullptr)
                return;

            parameters.set(0, parameterViewportSize = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEWPORT_SIZE.Value]);
        }

        virtual void updateParameters() override {
            parameterViewportSize->setValue(&XMFLOAT2((float)size.x, (float)size.y));
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        inline const WindowClass& getClass() const {
            return windowClass;
        }

        __declspec(property(get = getClass)) const WindowClass& Class;

        inline void setTitle(const String& title) {
            this->title = title;
            SetWindowText(handle, title);
        }

        inline const String& getTitle()const {
            return title;
        }

        __declspec(property(put = setTitle, get = getTitle)) String& Title;

        inline HWND getHandle() const {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        inline void setVisible(bool visible) {
            this->visible = visible;
            ShowWindow(handle, visible ? SW_SHOWNOACTIVATE : SW_HIDE);
        }

        inline bool isVisible() {
            return visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        Event<Window>& getOnCreated() {
            return onCreated;
        }

        __declspec(property(get = getOnCreated)) Event<Window>& OnCreated;

        Event<Window>& getOnDestroy() {
            return onDestroy;
        }

        __declspec(property(get = getOnDestroy)) Event<Window>& OnDestroy;

        Event<Window>& getOnPaint() {
            return onPaint;
        }

        __declspec(property(get = getOnPaint)) Event<Window>& OnPaint;

        inline const POINT& getPosition() const {
            return position;
        }

        inline void setPosition(const POINT& position) {
            setPosition(position.x, position.y);
        }

        void setPosition(int x, int y);

        __declspec(property(get = getPosition, put = setPosition)) POINT& Position;

        inline const XMINT2& getSize() const {
            return size;
        }

        inline void setSize(const XMINT2& size) {
            setSize(size.x, size.y);
        }

        void setSize(unsigned int w, unsigned int h);

        __declspec(property(get = getSize, put = setSize)) XMINT2& Size;

        inline unsigned int getWidth() const {
            return size.x;
        }

        __declspec(property(get = getWidth)) unsigned int Width;

        inline unsigned int getHeight() const {
            return size.y;
        }

        __declspec(property(get = getHeight)) unsigned int Height;

        Event<Window>& getOnPositionChanged() {
            return onPositionChanged;
        }

        __declspec(property(get = getOnPositionChanged)) Event<Window>& OnPositionChanged;

        Event<Window>& getOnSizeChanged() {
            return onSizeChanged;
        }

        __declspec(property(get = getOnSizeChanged)) Event<Window>& OnSizeChanged;

        Event<Window, KeyEventArgs>& getOnKeyEvent() {
            return onKeyEvent;
        }

        __declspec(property(get = getOnKeyEvent)) Event<Window, KeyEventArgs>& OnKeyEvent;

        Event<Window, MouseButtonEventArgs>& getOnMouseButtonEvent() {
            return onMouseButtonEvent;
        }

        __declspec(property(get = getOnMouseButtonEvent)) Event<Window, MouseButtonEventArgs>& OnMouseButtonEvent;

        Event<Window, MouseMotionEventArgs>& getOnMouseMotionEvent() {
            return onMouseMotionEvent;
        }

        __declspec(property(get = getOnMouseMotionEvent)) Event<Window, MouseMotionEventArgs>& OnMouseMotionEvent;

        Event<Window, MouseWheelEventArgs>& getOnMouseWheelEvent() {
            return onMouseWheelEvent;
        }

        __declspec(property(get = getOnMouseWheelEvent)) Event<Window, MouseWheelEventArgs>& OnMouseWheelEvent;

        inline void refresh() const {
            RedrawWindow(handle, nullptr, nullptr, RDW_INVALIDATE);
        }

        inline void activate() const {
            SetActiveWindow(handle);
        }

        FunctionQueue& getFunctionQueue() {
            return *functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue& FunctionQueue;

        inline bool handleMessages() {
            MSG msg = {};
            while (PeekMessage(&msg, handle, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT)
                    return false;
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            functionQueue->invoke();
            return true;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Window>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}