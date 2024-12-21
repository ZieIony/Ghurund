#include "ghuid2dpch.h"
#include "UILayer.h"

#include "core/resource/ResourceManager.h"
#include "engine/directx/SwapChain.h"
#include "engine/directx/Frame.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/direct2d/RenderTarget2D.h"
#include "ui/direct2d/UIContext.h"
#include "ui/direct2d/Graphics2d.h"
#include "ui/RootView.h"
#include <ui/constraint/WindowConstraint.h>

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine::DirectX;

    const Ghurund::Core::Type& D2DUILayer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<D2DUILayer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void D2DUILayer::init(Ghurund::UI::Direct2D::Graphics2D& graphics, Window& window, SwapChain& swapChain) {
        this->graphics = &graphics;
        this->swapChain = &swapChain;
        context = ghnew UIContext(graphics.D2DFactory, graphics.DWriteFactory, graphics.DeviceContext, window);
        __super::init(*context);
        canvas = ghnew Ghurund::UI::Direct2D::Canvas();
        canvas->init(graphics.DeviceContext);
        /*window.sizeChanging += [&](const Window& window, const IntSize& size) {
            renderTargets.clear();
            return true;
        };*/
        window.sizeChanged += [&](const Window& window) {
            rootView->requestLayout();
            return true;
        };
        initTargets();
    }

    void D2DUILayer::initTargets() {
        if (!swapChain->Initialized)
            return;
        for (Frame& frame : swapChain->Frames) {
            RenderTarget2D* target = ghnew RenderTarget2D();
            target->init(*graphics, *frame.RenderTarget.Texture);
            renderTargets.put(&frame.RenderTarget, std::shared_ptr<RenderTarget2D>(target));
        }
    }

    void D2DUILayer::uninitTargets() {
        renderTargets.clear();
    }

    void D2DUILayer::uninit() {
        if (!swapChain)
            return;
        renderTargets.clear();
        swapChain = nullptr;
        graphics = nullptr;
        delete canvas;
        canvas = nullptr;
        delete context;
        context = nullptr;
    }
    
    void D2DUILayer::draw(DirectXDrawingContext& context) {
        RenderTarget2D& renderTarget2d = *renderTargets.get(&context.RenderTarget).get();
		try {
			graphics->beginPaint(renderTarget2d);
            __super::draw(*canvas);
		} catch (...) {}
		try {
			graphics->endPaint(renderTarget2d);
		} catch (CallFailedException) {
			canvas->uninit();
			canvas->init(graphics->DeviceContext);
		}
	}
}