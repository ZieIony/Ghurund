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
            return false;// onMessage(msg, wParam, lParam);
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

        static LRESULT CALLBACK messageHandler(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
            WindowProc *windowProc = (WindowProc*)GetWindowLongPtr(handle, GWLP_USERDATA);

            if(msg==WM_CREATE) {
                LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;
                windowProc = (WindowProc*)createStruct->lpCreateParams;
                SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)windowProc);
                windowProc->init(handle);
           /*     windowProc->onCreate();
            } else if(msg==WM_KEYDOWN) {
                windowProc->onKeyDown(wParam);
            } else if(msg==WM_KEYUP) {
                windowProc->onKeyUp(wParam);
            } else if(msg==WM_LBUTTONDOWN) {
                windowProc->onMouseDown(MouseButton::LEFT);
            } else if(msg==WM_LBUTTONUP) {
                windowProc->onMouseUp(MouseButton::LEFT);
            } else if(msg==WM_MBUTTONDOWN) {
                windowProc->onMouseDown(MouseButton::MIDDLE);
            } else if(msg==WM_MBUTTONUP) {
                windowProc->onMouseUp(MouseButton::MIDDLE);
            } else if(msg==WM_RBUTTONDOWN) {
                windowProc->onMouseDown(MouseButton::RIGHT);
            } else if(msg==WM_RBUTTONUP) {
                windowProc->onMouseUp(MouseButton::RIGHT);
            } else if(msg==WM_MOUSEMOVE) {
                windowProc->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            } else if(msg==WM_MOUSEWHEEL) {
                windowProc->onMouseWheel(MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wParam));
            } else if(msg==WM_MOUSEHWHEEL) {
                windowProc->onMouseWheel(MouseWheel::HORIZONTAL, wParam);   // GET_WHEEL_DELTA_WPARAM(wParam) ?
            } else if(msg==WM_SIZE) {
                windowProc->onSizeChange();
            } else if(msg==WM_DESTROY) {
                windowProc->onDestroy();
                PostQuitMessage(0);*/
            } else if(windowProc==nullptr||!windowProc->handleMessage(msg, wParam, lParam)) {
                return DefWindowProc(handle, msg, wParam, lParam);
            }
            return 0;
        }
    };
}