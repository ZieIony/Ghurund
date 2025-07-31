#pragma once

#include "core/application/Layer.h"
#include "engine/directx/SwapChain.h"
#include "engine/directx/buffer/RenderTarget.h"
#include "ui/directx/DxCanvas.h"
#include "ui/directx/UIContext.h"
#include "ui/RootView.h"
#include "ui/UILayer.h"
#include "DxCanvas.h"

namespace Ghurund::UI::DirectX {
    using namespace ::Ghurund::Engine::DirectX;

    class DXUILayer:public Ghurund::UI::UILayer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DXUILayer::GET_TYPE();
#pragma endregion

    private:
        SwapChain* swapChain = nullptr;
        CommandList* commandList = nullptr;
        DxCanvas* canvas;
        IUIContext* context;

    public:
        ~DXUILayer() {
            uninit();
        }

        void init(Window& window, SwapChain& swapChain, CommandList& commandList);

        void uninit();

        inline IUIContext& getContext() {
            return *context;
        }

        __declspec(property(get = getContext)) IUIContext& Context;
    };
}