#pragma once

#include "core/application/Layer.h"
#include "engine/directx/SwapChain.h"
#include "engine/directx/buffer/RenderTarget.h"
#include "engine/directx/DirectXDrawingContext.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/direct2d/Canvas.h"
#include "ui/direct2d/Graphics2d.h"
#include "ui/direct2d/UIContext.h"
#include "ui/RootView.h"
#include "ui/UILayer.h"

namespace Ghurund::UI::Direct2D {
    using namespace ::Ghurund::Engine::DirectX;

    class D2DUILayer:public Ghurund::UI::UILayer<DirectXDrawingContext> {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = D2DUILayer::GET_TYPE();
#pragma endregion

    private:
        SwapChain* swapChain = nullptr;
        Graphics2D* graphics = nullptr;
        Ghurund::UI::Direct2D::Canvas* canvas;
        Map<RenderTarget*, std::shared_ptr<RenderTarget2D>> renderTargets;
        IUIContext* context;

    protected:
        virtual bool onSizeChanged() override {
            graphics->flush();
            return true;
        }

    public:
        ~D2DUILayer() {
            uninit();
        }

        void init(Ghurund::UI::Direct2D::Graphics2D& graphics, Window& window, SwapChain& swapChain);

        void initTargets();

        void uninitTargets();

        void uninit();

        inline RootView& getRootView() {
            return *rootView;
        }

        __declspec(property(get = getRoot)) RootView& RootView;

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

        virtual void draw(DirectXDrawingContext& context) override;
    };
}