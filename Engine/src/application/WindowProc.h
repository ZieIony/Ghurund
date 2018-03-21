#pragma once

#include "Ghurund.h"
#include "core/FunctionQueue.h"
#include "input/Input.h"
#include "input/Keyboard.h"
#include "Windowsx.h"
#include "input/Mouse.h"
#include "core/Logger.h"

namespace Ghurund {
    class WindowProc {
    private:
        HWND handle;
        FunctionQueue *functionQueue = nullptr;

        void init(HWND handle) {
            this->handle = handle;
            if(functionQueue!=nullptr)
                delete functionQueue;
            const unsigned int eventCode = RegisterWindowMessage(_T("GhurundEvent"));
            functionQueue = ghnew Ghurund::FunctionQueue(Handle, eventCode);
        }

        bool handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
            if(msg==functionQueue->getEventCode()) {
                functionQueue->take()();
                return true;
            }
            return onMessage(msg, wParam, lParam);
        }

    public:
        WindowProc() = default;

        virtual ~WindowProc() {
            delete functionQueue;
        }

        HWND getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        FunctionQueue &getFunctionQueue() {
            return *functionQueue;
        }

        __declspec(property(get = getFunctionQueue)) FunctionQueue &FunctionQueue;

        virtual void onCreate() {}

        virtual void onDestroy() {}

        virtual void onKey(KeyAction action, WPARAM key) {}

        virtual void onMouseButton(MouseButton button, MouseAction action) {}

        virtual void onMouseMove(int x, int y) {}

        virtual void onMouseWheel(MouseWheel wheel, short value) {}

        virtual void onSizeChange() {}

        virtual bool onMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
            return false;
        }

        /**
        * Domyslna funkcja obslugi wiadomosci dla aplikacji
        * okienkowej w systemie windows
        */
        static LRESULT CALLBACK messageHandler(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
            WindowProc *windowProc = (WindowProc*)GetWindowLongPtr(handle, GWLP_USERDATA);

            if(msg==WM_CREATE) {
                LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;
                windowProc = (WindowProc*)createStruct->lpCreateParams;
                SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)windowProc);
                windowProc->init(handle);
                windowProc->onCreate();
            } else if(msg==WM_KEYDOWN) {
                windowProc->onKey(KeyAction::DOWN, wParam);
            } else if(msg==WM_KEYUP) {
                windowProc->onKey(KeyAction::UP, wParam);
            } else if(msg==WM_LBUTTONDOWN) {
                windowProc->onMouseButton(MouseButton::LEFT, MouseAction::DOWN);
            } else if(msg==WM_LBUTTONUP) {
                windowProc->onMouseButton(MouseButton::LEFT, MouseAction::UP);
            } else if(msg==WM_MBUTTONDOWN) {
                windowProc->onMouseButton(MouseButton::MIDDLE, MouseAction::DOWN);
            } else if(msg==WM_MBUTTONUP) {
                windowProc->onMouseButton(MouseButton::MIDDLE, MouseAction::UP);
            } else if(msg==WM_RBUTTONDOWN) {
                windowProc->onMouseButton(MouseButton::RIGHT, MouseAction::DOWN);
            } else if(msg==WM_RBUTTONUP) {
                windowProc->onMouseButton(MouseButton::RIGHT, MouseAction::UP);
            } else if(msg==WM_MOUSEMOVE) {
                windowProc->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            } else if(msg==WM_MOUSEWHEEL) {
                windowProc->onMouseWheel(MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wParam));
            } else if(msg==WM_MOUSEHWHEEL) {
                windowProc->onMouseWheel(MouseWheel::HORIZONTAL, wParam);
            } else if(msg==WM_SIZE) {
                windowProc->onSizeChange();
            } else if(msg==WM_DESTROY) {
                windowProc->onDestroy();
                PostQuitMessage(0);
            } else if(windowProc==nullptr||!windowProc->handleMessage(msg, wParam, lParam)) {
                return DefWindowProc(handle, msg, wParam, lParam);
            }
            return 0;
        }
    };
}