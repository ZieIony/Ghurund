#pragma once

#include "application/Logger.h"
#include "core/threading/FunctionQueue.h"

#include <Windowsx.h>
#include <time.h>

namespace Ghurund {
    struct SystemMessage {
        unsigned int code;
        WPARAM wParam;
        LPARAM lParam;
        time_t time;
    };

    class WindowProc {
    private:
        HWND handle;
        FunctionQueue *functionQueue = nullptr;
        std::function<bool(SystemMessage&)> messageHandler;

        void init(HWND handle) {
            this->handle = handle;
            if(functionQueue!=nullptr)
                delete functionQueue;
            const unsigned int eventCode = RegisterWindowMessage(_T("GhurundEvent"));
            functionQueue = ghnew Ghurund::FunctionQueue(Handle, eventCode);
        }

        bool handleMessage(SystemMessage &message) {
            if(message.code==functionQueue->getEventCode()) {
                functionQueue->take()();
                return true;
            }
            return messageHandler(message);
        }

    public:
        WindowProc(std::function<bool(SystemMessage&)> &messageHandler):messageHandler(messageHandler) {}

        ~WindowProc() {
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

        static LRESULT CALLBACK messageProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
            WindowProc *windowProc = (WindowProc*)GetWindowLongPtr(handle, GWLP_USERDATA);

            if(msg==WM_CREATE) {
                LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;
                windowProc = (WindowProc*)createStruct->lpCreateParams;
                SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)windowProc);
                windowProc->init(handle);
            } 
            
            SystemMessage message = {msg, wParam, lParam, time(nullptr)};
            if(windowProc!=nullptr&&windowProc->handleMessage(message))
                return 0;
            return DefWindowProc(handle, msg, wParam, lParam);
        }
    };
}