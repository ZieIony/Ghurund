#pragma once

#include "Window.h"
#include "core/threading/FunctionQueue.h"

namespace Ghurund::Core {
    class ChildWindow:public Window {
    public:
        ChildWindow(Window& parent):Window(&parent) {}

        virtual Ghurund::Core::FunctionQueue& getFunctionQueue() override {
            return Parent->FunctionQueue;
        }
    };
}