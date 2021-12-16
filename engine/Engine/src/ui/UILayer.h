#pragma once

#include "ui/direct2d/Canvas.h"
#include "ui/RootView.h"
#include "application/Layer.h"
#include "ui/direct2d/Graphics2d.h"

namespace Ghurund::UI {
    using namespace Ghurund::UI::Direct2D;

    class UILayer:public Layer {
    private:
        Graphics2D& graphics;
        Ghurund::UI::Direct2D::Canvas* canvas;
        RootView* rootView;
        Map<RenderTarget*, std::shared_ptr<RenderTarget2D>> renderTargets;

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
        UILayer(Graphics2D& graphics, RootView* rootView, ApplicationWindow* window):graphics(graphics) {
            canvas = ghnew Ghurund::UI::Direct2D::Canvas();
            canvas->init(graphics.DeviceContext);
            this->rootView = rootView;
            rootView->addReference();
            if (window) {
                SwapChain& swapChain = window->SwapChain;
                window->sizeChanging += [&](const Window& window, const IntSize& size) {
                    renderTargets.clear();
                    return true;
                };
                window->sizeChanged += [&](const Window& window) {
                    for (Frame& frame : swapChain.Frames) {
                        RenderTarget2D* target = ghnew RenderTarget2D();
                        target->init(graphics, *frame.RenderTarget.Texture);
                        renderTargets.set(&frame.RenderTarget, std::shared_ptr<RenderTarget2D>(target));
                    }
                    return true;
                };
            }
        }

        ~UILayer() {
            rootView->release();
            delete canvas;
        }

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