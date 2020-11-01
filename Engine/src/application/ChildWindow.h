#pragma once

#include "Window.h"

namespace Ghurund {
    class ChildWindow:public Window {
    public:
        ChildWindow(Window& parent):Window(&parent) {}

        virtual Ghurund::FunctionQueue& getFunctionQueue() override {
            return Parent->FunctionQueue;
        }
    };
}