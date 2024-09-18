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

    class DXUILayer:public Ghurund::UI::UILayer<RenderTarget> {
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
        DxCanvas* canvas;
        IUIContext* context;

    public:
        ~DXUILayer() {
            uninit();
        }

        void init(Window& window, SwapChain& swapChain);

        void uninit();

        inline RootView& getRoot() {
            return *rootView;
        }

        __declspec(property(get = getRoot)) RootView& Root;

        inline IUIContext& getContext() {
            return *context;
        }

        __declspec(property(get = getContext)) IUIContext& Context;

        virtual bool dispatchKeyEvent(const KeyEventArgs& args) {
            return rootView->dispatchKeyEvent(args);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& args) {
            return rootView->dispatchMouseButtonEvent(args);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& args) {
            return rootView->dispatchMouseMotionEvent(args);
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            return rootView->dispatchMouseWheelEvent(args);
        }

        virtual void draw(RenderTarget& context) override;
    };
}