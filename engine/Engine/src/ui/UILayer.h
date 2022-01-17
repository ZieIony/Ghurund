#pragma once

#include "application/Layer.h"
#include "ui/RootView.h"
#include "ui/direct2d/Canvas.h"
#include "ui/direct2d/Graphics2d.h"
#include "ui/direct2d/UIContext.h"

namespace Ghurund::UI {
    using namespace Ghurund::UI::Direct2D;

    class UILayer:public Layer {
    private:
        Graphics2D& graphics;
        Ghurund::UI::Direct2D::Canvas* canvas;
        RootView* rootView;
        Map<RenderTarget*, std::shared_ptr<RenderTarget2D>> renderTargets;
        IUIContext* context;
        ApplicationWindow& window;

    protected:
        virtual bool onSizeChangedEvent() override {
            graphics.flush();
            return true;
        }

        virtual bool onFocusedChangedEvent() override {
            rootView->Focused = Focused;
            return true;
        }

    public:
        UILayer(Graphics2D& graphics, ApplicationWindow& window, ResourceManager& resourceManager):graphics(graphics), window(window) {
            context = ghnew UIContext(*graphics.D2DFactory, *graphics.DWriteFactory, graphics.DeviceContext, window, resourceManager);
            canvas = ghnew Ghurund::UI::Direct2D::Canvas();
            canvas->init(graphics.DeviceContext);
            this->rootView = ghnew Ghurund::UI::RootView(*context);
            SwapChain& swapChain = window.SwapChain;
            window.sizeChanging += [&](const Window& window, const IntSize& size) {
                renderTargets.clear();
                return true;
            };
            window.sizeChanged += [&](const Window& window) {
                initTargets();
                return true;
            };
            initTargets();
        }

        ~UILayer() {
            rootView->release();
            delete canvas;
            delete context;
        }

        void initTargets() {
            SwapChain& swapChain = window.SwapChain;
            for (Frame& frame : swapChain.Frames) {
                RenderTarget2D* target = ghnew RenderTarget2D();
                target->init(graphics, *frame.RenderTarget.Texture);
                renderTargets.set(&frame.RenderTarget, std::shared_ptr<RenderTarget2D>(target));
            }
        }

        inline RootView& getRoot() {
            return *rootView;
        }

        __declspec(property(get = getRoot)) RootView& Root;

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

        virtual void update(const uint64_t time) override {
            rootView->onUpdate(time);
            rootView->measure((float)Size.width, (float)Size.height);
            rootView->layout(0, 0, (float)Size.width, (float)Size.height);
        }

        virtual Status draw(RenderTarget& renderTarget) override {
            RenderTarget2D* target2d = renderTargets.get(&renderTarget).get();
            if (graphics.beginPaint(*target2d) == Status::OK) {
                canvas->beginPaint();
                rootView->draw(*canvas);
                canvas->endPaint();
            }
            Status result = graphics.endPaint(*target2d);
            if (result != Status::OK) {
                canvas->uninit();
                canvas->init(graphics.DeviceContext);
            }
            return result;
        }
    };
}