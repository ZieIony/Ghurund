#include "ghuidxpch.h"
#include "UILayer.h"

#include "engine/directx/SwapChain.h"
#include "ui/directx/UIContext.h"
#include "ui/RootView.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine::DirectX;

    const Ghurund::Core::Type& DXUILayer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DXUILayer>(Ghurund::UI::DirectX::NAMESPACE_NAME, GH_STRINGIFY(DXUILayer))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DXUILayer::init(Window& window, SwapChain& swapChain) {
        this->swapChain = &swapChain;
        context = ghnew UIContext(window);
        __super::init(*context);
        canvas = ghnew DxCanvas();
        canvas->init(window.Size);
        window.sizeChanged += [&](const Window& window) {
            rootView->requestLayout();
            return true;
        };
    }

    void DXUILayer::uninit() {
        if (!swapChain)
            return;
        swapChain = nullptr;
        delete canvas;
        canvas = nullptr;
        delete context;
        context = nullptr;
    }
    
    void DXUILayer::draw(RenderTarget& context) {
        __super::draw(*canvas);
	}
}