#include "ghuidxpch.h"
#include "DXUILayer.h"

#include "engine/directx/SwapChain.h"
#include "ui/directx/UIContext.h"
#include "ui/RootView.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine::DirectX;

    const Ghurund::Core::Type& DXUILayer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DXUILayer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DXUILayer::init(Window& window, SwapChain& swapChain, CommandList& commandList) {
        this->swapChain = &swapChain;
        this->commandList = &commandList;
        context = ghnew UiContext(window);
        __super::init(*context);
    }

    void DXUILayer::uninit() {
        if (!swapChain)
            return;
        swapChain = nullptr;
        delete context;
        context = nullptr;
    }
    
    /*void DXUILayer::draw(RenderTarget& context) {
        canvas->setContext(*commandList, context);
        __super::draw(*canvas);
	}*/
}