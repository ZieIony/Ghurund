module;

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "core/application/Application.h"
#include "Status.h"

#include <windowsx.h>

module Ghurund.Engine.Application.ApplicationWindow;

import Ghurund.Engine.Application.LayerList;
import Ghurund.Engine.UI.UIFeature;

namespace Ghurund {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& ApplicationWindow::GET_TYPE() {
        static auto PROPERTY_SWAPCHAIN = Property<ApplicationWindow, Ghurund::Core::DirectX::SwapChain&>("SwapChain", &getSwapChain);
        static auto PROPERTY_LAYERS = Property<ApplicationWindow, LayerList&>("Layers", &getLayers);
        static auto PROPERTY_APPLICATION = Property<ApplicationWindow, Ghurund::Core::Application&>("Application", &getApplication);

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

    ApplicationWindow::ApplicationWindow(Ghurund::Core::Application& app, Renderer& renderer):SystemWindow(app.Timer), app(app), renderer(renderer) {}

    void ApplicationWindow::init(WindowManager& windowManager) {
        __super::init(windowManager);
        swapChain = ghnew Ghurund::Core::DirectX::SwapChain();
        Ghurund::Core::DirectX::Graphics& graphics = app.Features.get<Ghurund::Core::DirectX::Graphics>();
        swapChain->init(graphics, *this);
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

    bool ApplicationWindow::onMouseWheelEvent(const Ghurund::Core::MouseWheelEventArgs& args) {
        return layers.dispatchMouseWheelEvent(args);
    }

    void ApplicationWindow::update(const uint64_t time) {
        __super::update(time);
        layers.update(time);
    }

    Status ApplicationWindow::paint() {
        Ghurund::Core::DirectX::Frame& frame = swapChain->CurrentFrame;
        Ghurund::Core::DirectX::CommandList& commandList = renderer.startFrame(frame);
        //levelManager.draw(commandList);
        frame.flush();

        Status result = layers.draw(frame.RenderTarget);
        if (result != Status::OK)
            return result;

        result = renderer.finishFrame(frame);
        if (result != Status::OK)
            return result;
        return swapChain->present();
    }

}