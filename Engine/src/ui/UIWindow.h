#pragma once

#include "RootView.h"
#include "application/Window.h"
#include "application/WindowType.h"
#include "ui/gdi/GdiCanvas.h"

namespace Ghurund::UI {
    class UIWindow {
    private:
        Window* window;
        RootView* rootView;
        Canvas* canvas;

    public:
        UIWindow(const WindowClass& type, const Window* parent = nullptr);

        ~UIWindow() {
            delete canvas;
            rootView->release();
            delete window;
        }

        inline RootView* getRootView() {
            return rootView;
        }

        __declspec(property(get = getRootView)) RootView* RootView;

        inline Window& getWindow() {
            return *window;
        }

        __declspec(property(get = getWindow)) Window& Window;
    };
}