#include "ghpch.h"
#include "ApplicationWindow.h"
#include "Application.h"

#include <windowsx.h>

namespace Ghurund {
    const Ghurund::Type& ApplicationWindow::GET_TYPE() {
        static const Ghurund::Type TYPE = Ghurund::TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ApplicationWindow))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool ApplicationWindow::onFocusedChangedEvent() {
        if (Focused) {
            layers.restoreFocus();
        } else {
            layers.clearFocus();
        }
        return true;
    }

    ApplicationWindow::ApplicationWindow(const WindowClass& type, Ghurund::Application& app):SystemWindow(type, app.Timer), app(app) {}

    bool ApplicationWindow::onKeyEvent(const KeyEventArgs& args) {
        return layers.dispatchKeyEvent(args);
    }

    bool ApplicationWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
        bool consumed = layers.dispatchMouseButtonEvent(args);
        if (consumed && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
            SetCapture(Handle);
        } else {
            ReleaseCapture();
        }
        return consumed;
    }

    bool ApplicationWindow::onMouseMotionEvent(const MouseMotionEventArgs& args) {
        return layers.dispatchMouseMotionEvent(args);
    }

    bool ApplicationWindow::onMouseWheelEvent(const MouseWheelEventArgs& args) {
        return layers.dispatchMouseWheelEvent(args);
    }

    void ApplicationWindow::update(const uint64_t time) {
        __super::update(time);
        layers.update(time);
    }

}