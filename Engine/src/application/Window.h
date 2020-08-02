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

    class Window: public ParameterProvider, public NamedObject<String>, public Object {
    private:
        inline static const tchar* WINDOW_CLASS_NAME = _T("Ghurund");
        inline static const char* CLASS_NAME = GH_STRINGIFY(Window);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Window>();

        String title;
        WNDCLASSEX windowClass;
        HWND handle;
        HINSTANCE hInst;
        bool visible;
        XMINT2 size;

        PointerArray<Parameter*> parameters;
        ValueParameter* parameterViewportSize = nullptr;

        Event<Window> onCreated;
        Event<Window> onSizeChanged;
        Event<Window> onPaint;
        Event<Window> onDestroy;

        Event<Window, KeyEventArgs> onKeyEvent;
        Event<Window, MouseButtonEventArgs> onMouseButtonEvent;
        POINT prevMousePos = {-1, -1};
        Event<Window, MouseMotionEventArgs> onMouseMotionEvent;
        Event<Window, MouseWheelEventArgs> onMouseWheelEvent;

        FunctionQueue* functionQueue = nullptr;

        static LRESULT CALLBACK messageProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
        static void handleMouseMessage(Window& window, UINT msg, WPARAM wParam);

    public:
        Window():parameters(PointerArray<Parameter*>(1)) {
            Name = _T("window");
        }

        ~Window() {
            uninit();
        }

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

        void init(HWND handle);
        void init(Settings& settings);

        void uninit();

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
            ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
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

        inline const XMINT2& getSize() const {
            return size;
        }

        inline void setSize(const XMINT2& size) {
            setSize(size.x, size.y);
        }

        inline void setSize(unsigned int w, unsigned int h) {
            if (size.x != w || size.y != h) {
                size = XMINT2(w, h);

                RECT rc, rcClient;
                GetWindowRect(handle, &rc);
                GetClientRect(handle, &rcClient);
                int xExtra = rc.right - rc.left - rcClient.right;
                int yExtra = rc.bottom - rc.top - rcClient.bottom;

                SetWindowPos(handle, HWND_TOPMOST, 0, 0, w + xExtra, h + yExtra, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);
            }
        }

        __declspec(property(get = getSize, put = setSize)) XMINT2& Size;

        inline unsigned int getWidth() const {
            return size.x;
        }

        __declspec(property(get = getWidth)) unsigned int Width;

        inline unsigned int getHeight() const {
            return size.y;
        }

        __declspec(property(get = getHeight)) unsigned int Height;

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

        void refresh() const {
            RedrawWindow(handle, nullptr, nullptr, RDW_INVALIDATE);
        }

        FunctionQueue& getFunctionQueue() {
            return *functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue& FunctionQueue;

		inline static const Ghurund::Type& TYPE = TypeBuilder<Window>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Object::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}