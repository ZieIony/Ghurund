#include "Direct2DWindow.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/resource/ResourceManager.h"

#include <windowsx.h>

namespace Samples {
    const Ghurund::Core::Type& Direct2DWindow::GET_TYPE() {

        static const Ghurund::Core::Type TYPE = TypeBuilder<Direct2DWindow>("Ghurund", "Direct2DWindow")
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool Direct2DWindow::onFocusedChangedEvent() {
        rootView->Focused = Focused;
        return true;
    }

    Direct2DWindow::Direct2DWindow(Ghurund::Core::Timer& timer):SystemWindow(timer) {}

    void Direct2DWindow::init(WindowManager& windowManager) {
        __super::init(windowManager);
        /*canvas = ghnew Canvas();
        canvas->init(Handle);
        resourceManager = ghnew ResourceManager();
        uiContext = ghnew UIContext(*this, *resourceManager);
        rootView = ghnew RootView(*uiContext);*/
    }

    void Direct2DWindow::uninit() {
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

    bool Direct2DWindow::onKeyEvent(const KeyEventArgs& args) {
        return rootView->dispatchKeyEvent(args);
    }

    bool Direct2DWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
        bool consumed = rootView->dispatchMouseButtonEvent(args);
        if (consumed && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
            SetCapture(Handle);
        } else {
            ReleaseCapture();
        }
        return consumed;
    }

    bool Direct2DWindow::onMouseMotionEvent(const MouseMotionEventArgs& args) {
        return rootView->dispatchMouseMotionEvent(args);
    }

    bool Direct2DWindow::onMouseWheelEvent(const MouseWheelEventArgs& args) {
        return rootView->dispatchMouseWheelEvent(args);
    }

    void Direct2DWindow::update(const uint64_t time) {
        __super::update(time);
        rootView->onUpdate(time);
        rootView->measure((float)Size.Width, (float)Size.Height);
        rootView->layout(0, 0, (float)Size.Width, (float)Size.Height);
    }

    Status Direct2DWindow::paint() {
        /*canvas->beginPaint();
        rootView->draw(*canvas);
        canvas->endPaint();*/
        return Status::OK;
    }

}