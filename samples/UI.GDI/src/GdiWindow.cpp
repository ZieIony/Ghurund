#include "GdiWindow.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/resource/ResourceManager.h"

#include <windowsx.h>

namespace Samples {
    const Ghurund::Core::Type& GdiWindow::GET_TYPE() {

        static const Ghurund::Core::Type TYPE = TypeBuilder<GdiWindow>("Ghurund", "GdiWindow")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool GdiWindow::onFocusedChangedEvent() {
        rootView->Focused = Focused;
        return true;
    }

    GdiWindow::GdiWindow(Ghurund::Core::Timer& timer):SystemWindow(timer) {}

    void GdiWindow::init(WindowManager& windowManager) {
        __super::init(windowManager);
        canvas = ghnew Canvas();
        canvas->init(Handle);
        resourceManager = ghnew ResourceManager();
        uiContext = ghnew UIContext(*this, *resourceManager);
        rootView = ghnew RootView(*uiContext);
    }

    void GdiWindow::uninit() {
        if (rootView) {
            rootView->release();
            rootView = nullptr;
        }
        if (uiContext) {
            delete uiContext;
            uiContext = nullptr;
        }
        if (canvas) {
            delete canvas;
            canvas = nullptr;
        }
        if (resourceManager) {
            delete resourceManager;
            resourceManager = nullptr;
        }
    }

    bool GdiWindow::onKeyEvent(const KeyEventArgs& args) {
        return rootView->dispatchKeyEvent(args);
    }

    bool GdiWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
        bool consumed = rootView->dispatchMouseButtonEvent(args);
        if (consumed && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
            SetCapture(Handle);
        } else {
            ReleaseCapture();
        }
        return consumed;
    }

    bool GdiWindow::onMouseMotionEvent(const MouseMotionEventArgs& args) {
        return rootView->dispatchMouseMotionEvent(args);
    }

    bool GdiWindow::onMouseWheelEvent(const MouseWheelEventArgs& args) {
        return rootView->dispatchMouseWheelEvent(args);
    }

    void GdiWindow::update(const uint64_t time) {
        __super::update(time);
        rootView->onUpdate(time);
        rootView->measure((float)Size.Width, (float)Size.Height);
        rootView->layout(0, 0, (float)Size.Width, (float)Size.Height);
    }

    Status GdiWindow::paint() {
        /*canvas->beginPaint();
        rootView->draw(*canvas);
        canvas->endPaint();*/
        return Status::OK;
    }

}