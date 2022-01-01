#include "ghpch.h"
#include "ApplicationWindow.h"

#include "Application.h"
#include "graphics/Renderer.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

#include <windowsx.h>
#include <ui/UIFeature.h>

namespace Ghurund {
    const Ghurund::Core::Type& ApplicationWindow::GET_TYPE() {
        static auto PROPERTY_SWAPCHAIN = Ghurund::ReadOnlyProperty<ApplicationWindow, Ghurund::SwapChain&>("SwapChain", (Ghurund::SwapChain & (ApplicationWindow::*)()) & getSwapChain);
        static auto PROPERTY_LAYERS = Ghurund::ReadOnlyProperty<ApplicationWindow, LayerList&>("Layers", (LayerList & (ApplicationWindow::*)()) & getLayers);
        static auto PROPERTY_APPLICATION = Ghurund::ReadOnlyProperty<ApplicationWindow, Ghurund::Application&>("Application", (Ghurund::Application & (ApplicationWindow::*)()) & getApplication);

        static const Ghurund::Core::Type TYPE = TypeBuilder<ApplicationWindow>("Ghurund", "ApplicationWindow")
            .withProperty(PROPERTY_SWAPCHAIN)
            .withProperty(PROPERTY_LAYERS)
            .withProperty(PROPERTY_APPLICATION)
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

    ApplicationWindow::ApplicationWindow(Ghurund::Application& app):SystemWindow(app.Timer), app(app) {}

    void ApplicationWindow::init(WindowManager& windowManager) {
        __super::init(windowManager);
        swapChain = ghnew Ghurund::SwapChain();
        swapChain->init(app.Graphics, *this);
        swapChain->initBuffers();
    }

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

    Status ApplicationWindow::paint() {
        Frame& frame = swapChain->CurrentFrame;
        CommandList& commandList = app.Renderer.startFrame(frame);
        //levelManager.draw(commandList);
        frame.flush();

        Status result = layers.draw(frame.RenderTarget);
        if (result != Status::OK)
            return result;

        result = app.Renderer.finishFrame(frame);
        if (result != Status::OK)
            return result;
        return swapChain->present();
    }

}