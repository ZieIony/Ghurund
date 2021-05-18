#include "ghpch.h"
#include "ApplicationWindow.h"
#include "Application.h"
#include "graphics/Renderer.h"

#include <windowsx.h>
#include <ui/UIFeature.h>

namespace Ghurund {
    bool ApplicationWindow::onFocusedChangedEvent() {
        if (Focused) {
            layers.restoreFocus();
        } else {
            layers.clearFocus();
        }
        return true;
    }

    ApplicationWindow::ApplicationWindow(const WindowClass& type, Ghurund::Application& app):SystemWindow(type, app.Timer), app(app) {
        Graphics2D* graphics2d = nullptr;
        UIFeature* uiFeature = app.Features.get<UIFeature>();
        if (uiFeature) {
            graphics2d = &uiFeature->Graphics2D;
            swapChain = ghnew Ghurund::SwapChain();
        }
        swapChain->init(app.Graphics, graphics2d, *this);
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
        if (Size.width == 0 && Size.height == 0)
            return Status::OK;
        Frame& frame = swapChain->CurrentFrame;
        CommandList& commandList = app.Renderer.startFrame(frame);
        //levelManager.draw(commandList);
        frame.flush();

        Status result = layers.draw(swapChain->CurrentFrame.RenderTarget);
        if (result != Status::OK)
            return result;

        result = app.Renderer.finishFrame(frame);
        if (result != Status::OK)
            return result;
        return swapChain->present();
    }

}