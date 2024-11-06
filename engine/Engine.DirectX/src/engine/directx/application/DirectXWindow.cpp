#include "ghedxpch.h"

#include "DirectXWindow.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/window/SystemWindow.h"
#include "core/application/Application.h"
#include "core/application/LayerList.h"

#include <windowsx.h>

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& DirectXWindow::GET_TYPE() {
        static auto PROPERTY_SWAPCHAIN = Property<DirectXWindow, Ghurund::Engine::DirectX::SwapChain&>("SwapChain", &getSwapChain);
        static auto PROPERTY_LAYERS = Property<DirectXWindow, LayerList<DirectXDrawingContext>&>("Layers", &getLayers);
        static auto PROPERTY_APPLICATION = Property<DirectXWindow, Ghurund::Core::Application&>("Application", &getApplication);

        static const Ghurund::Core::Type TYPE = TypeBuilder<DirectXWindow>()
            .withProperty(PROPERTY_SWAPCHAIN)
            .withProperty(PROPERTY_LAYERS)
            .withProperty(PROPERTY_APPLICATION)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool DirectXWindow::onFocusedChangedEvent() {
        if (Focused) {
            layers.restoreFocus();
        } else {
            layers.clearFocus();
        }
        return true;
    }

    DirectXWindow::DirectXWindow(Ghurund::Core::Application& app, Renderer& renderer):SystemWindow(app.Timer), app(app), renderer(renderer) {}

    void DirectXWindow::init(WindowManager& windowManager) {
        __super::init(windowManager);
        swapChain = ghnew Ghurund::Engine::DirectX::SwapChain();
        Ghurund::Engine::DirectX::Graphics& graphics = app.Features.get<Ghurund::Engine::DirectX::Graphics>();
        swapChain->init(graphics, *this);
        swapChain->initBuffers();
    }

    bool DirectXWindow::onKeyEvent(const KeyEventArgs& args) {
        return layers.dispatchKeyEvent(args);
    }

    bool DirectXWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
        bool consumed = layers.dispatchMouseButtonEvent(args);
        if (consumed && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
            SetCapture(Handle);
        } else {
            ReleaseCapture();
        }
        return consumed;
    }

    bool DirectXWindow::onMouseMotionEvent(const MouseMotionEventArgs& args) {
        return layers.dispatchMouseMotionEvent(args);
    }

    bool DirectXWindow::onMouseWheelEvent(const Ghurund::Core::MouseWheelEventArgs& args) {
        return layers.dispatchMouseWheelEvent(args);
    }

    void DirectXWindow::update(const uint64_t time) {
        __super::update(time);
        layers.update(time);
    }

    void DirectXWindow::paint() {
        Ghurund::Engine::DirectX::Frame& frame = swapChain->CurrentFrame;
        Ghurund::Engine::DirectX::CommandList& commandList = renderer.startFrame(frame);
        //levelManager.draw(commandList);
        frame.flush();
        auto drawingContext = DirectXDrawingContext(frame.RenderTarget);
        layers.draw(drawingContext);
        renderer.finishFrame(frame);
        swapChain->present();
    }

}

namespace Ghurund::Core {
    template<>
    const Type& getType<LayerList<Ghurund::Engine::DirectX::DirectXDrawingContext>>() {
        static Type TYPE = TypeBuilder<LayerList<Ghurund::Engine::DirectX::DirectXDrawingContext>>();
        return TYPE;
    }
}