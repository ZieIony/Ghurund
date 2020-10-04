#include "UIWindow.h"

namespace Ghurund::UI {
    UIWindow::UIWindow(const WindowClass& type, const Ghurund::Window* parent) {
        window = type.create(parent);
        rootView = ghnew Ghurund::UI::RootView(*window);
        canvas = ghnew GdiCanvas(window->Handle);

        window->OnSizeChanged.add([this](Ghurund::Window& window) {
            rootView->invalidate();
            return true;
        });

        window->OnKeyEvent.add([this](Ghurund::Window& window, const KeyEventArgs& args) {
            rootView->dispatchKeyEvent(args);
            return true;
        });

        window->OnMouseButtonEvent.add([this](Ghurund::Window& window, const MouseButtonEventArgs& args) {
            rootView->dispatchMouseButtonEvent(args);
            return true;
        });

        window->OnMouseMotionEvent.add([this](Ghurund::Window& window, const MouseMotionEventArgs& args) {
            rootView->dispatchMouseMotionEvent(args);
            return true;
        });

        window->OnMouseWheelEvent.add([this](Ghurund::Window& window, const MouseWheelEventArgs& args) {
            rootView->dispatchMouseWheelEvent(args);
            return true;
        });

        window->OnPaint.add([this](const Ghurund::Window& window) {
            canvas->beginPaint();
            rootView->draw(*canvas);
            canvas->endPaint();
            return true;
        });
    }
}
