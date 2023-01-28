module;

#include "core/resource/ResourceManager.h"
#include "core/directx/SwapChain.h"
#include "core/directx/Frame.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/direct2d/RenderTarget2D.h"
#include "ui/direct2d/UIContext.h"
#include "ui/direct2d/Graphics2d.h"

module Ghurund.Engine.UI.UILayer;

namespace Ghurund {
    using namespace Ghurund::Core;
    using namespace Ghurund::Core::DirectX;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

    UILayer::UILayer(Ghurund::UI::Direct2D::Graphics2D& graphics, ApplicationWindow& window, ResourceManager& resourceManager):graphics(graphics), window(window) {
        context = ghnew UIContext(*graphics.D2DFactory, *graphics.DWriteFactory, graphics.DeviceContext, window, resourceManager);
        canvas = ghnew Ghurund::UI::Direct2D::Canvas();
        canvas->init(graphics.DeviceContext);
        this->rootView = ghnew Ghurund::UI::RootView(*context);
        rootView->setConstraints({
            .width = std::make_shared<ValueConstraint>((float)window.Size.Width),
            .height = std::make_shared<ValueConstraint>((float)window.Size.Height)
            });
        SwapChain& swapChain = window.SwapChain;
        window.sizeChanging += [&](const Window& window, const IntSize& size) {
            renderTargets.clear();
            return true;
        };
        window.sizeChanged += [&](const Window& window) {
            initTargets();
            rootView->setConstraints({
       .width = std::make_shared<ValueConstraint>((float)window.Size.Width),
       .height = std::make_shared<ValueConstraint>((float)window.Size.Height)
                });
            rootView->invalidate();
            return true;
        };
        initTargets();
    }
    
    void UILayer::initTargets() {
        SwapChain& swapChain = window.SwapChain;
        if (!swapChain.Initialized)
            return;
        for (Frame& frame : swapChain.Frames) {
            RenderTarget2D* target = ghnew RenderTarget2D();
            target->init(graphics, *frame.RenderTarget.Texture);
            renderTargets.set(&frame.RenderTarget, std::shared_ptr<RenderTarget2D>(target));
        }
    }
    
    void UI::UILayer::update(const uint64_t time) {
        rootView->onUpdate(time);
        graph.clear();
        rootView->resolveConstraints(graph);
        graph.sort();
        graph.evaluate();
        rootView->measure((float)Size.Width, (float)Size.Height);
        rootView->layout(0, 0, (float)Size.Width, (float)Size.Height);
    }

    Status UILayer::draw(RenderTarget& renderTarget) {
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
}