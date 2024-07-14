#pragma once

#include "core/application/Layer.h"
#include "core/directx/SwapChain.h"
#include "core/directx/buffer/RenderTarget.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/direct2d/Canvas.h"
#include "ui/direct2d/Graphics2d.h"
#include "ui/direct2d/UIContext.h"
#include "ui/RootView.h"
#include "ui/UILayer.h"

namespace Ghurund::UI::Direct2D {
    using namespace ::Ghurund::Core::DirectX;

    class D2DUILayer:public Ghurund::UI::UILayer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = UILayer::GET_TYPE();
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

        virtual void draw(IDrawingContext& drawingContext) override;
    };
}