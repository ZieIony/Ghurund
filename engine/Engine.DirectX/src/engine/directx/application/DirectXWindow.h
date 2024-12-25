#pragma once

#include "core/application/Application.h"
#include "core/application/ApplicationWindow.h"
#include "core/application/LayerList.h"
#include "engine/directx/DirectXDrawingContext.h"
#include "engine/directx/Renderer.h"
#include "engine/directx/SwapChain.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DirectXWindow: public Ghurund::Core::ApplicationWindow<Ghurund::Engine::DirectX::DirectXDrawingContext>{
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DirectXWindow::GET_TYPE();
#pragma endregion

    private:
        SwapChain* swapChain = nullptr;
        Renderer& renderer;

    protected:
        virtual bool onSizeChangedEvent() override;

    public:
        DirectXWindow(Ghurund::Core::Application& app, Renderer& renderer);

        ~DirectXWindow() {
            delete swapChain;
            swapChain = nullptr;
        }

        virtual void init() override;

        inline SwapChain& getSwapChain() {
            return *swapChain;
        }

        __declspec(property(get = getSwapChain)) Ghurund::Engine::DirectX::SwapChain& SwapChain;

        virtual void paint() override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<LayerList<Ghurund::Engine::DirectX::DirectXDrawingContext>>();
}