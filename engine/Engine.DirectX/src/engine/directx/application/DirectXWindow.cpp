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
        static auto PROPERTY_APPLICATION = Property<DirectXWindow, Ghurund::Core::Application&>("Application", &getApplication);

        static const Ghurund::Core::Type TYPE = TypeBuilder<DirectXWindow>()
            .withProperty(PROPERTY_SWAPCHAIN)
            .withProperty(PROPERTY_APPLICATION)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool DirectXWindow::onSizeChangedEvent() {
        if (swapChain)
            swapChain->uninitBuffers();
        bool result = __super::onSizeChangedEvent();
		if (swapChain && Size.Width > 0 && Size.Height > 0) {
            swapChain->resize(Size);
            swapChain->initBuffers();
        }
        return result;
    }

    DirectXWindow::DirectXWindow(Ghurund::Core::Application& app, Renderer& renderer):ApplicationWindow(app), renderer(renderer) {}

    void DirectXWindow::init() {
        __super::init();
        swapChain = ghnew Ghurund::Engine::DirectX::SwapChain();
        Ghurund::Engine::DirectX::Graphics& graphics = Application.Features.get<Ghurund::Engine::DirectX::Graphics>();
        swapChain->init(graphics, *this);
        swapChain->initBuffers();
    }

    void DirectXWindow::paint() {
        Ghurund::Engine::DirectX::Frame& frame = swapChain->CurrentFrame;
        Ghurund::Engine::DirectX::CommandList& commandList = renderer.startFrame(frame);
        //levelManager.draw(commandList);
        frame.flush();
        auto drawingContext = DirectXDrawingContext(frame.RenderTarget);
        Layers.draw(drawingContext);
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