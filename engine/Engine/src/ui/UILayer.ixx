module;

#include "ui/RootView.h"
#include "ui/direct2d/Canvas.h"
#include "ui/direct2d/Graphics2d.h"
#include "ui/direct2d/UIContext.h"
#include "core/directx/buffer/RenderTarget.h"

export module Ghurund.Engine.UI.UILayer;

import Ghurund.Engine.Application.Layer;
import Ghurund.Engine.Application.ApplicationWindow;

export namespace Ghurund::UI {
    using namespace Ghurund::UI::Direct2D;
    using namespace Ghurund::Core::DirectX;

    class UILayer:public Layer {
    private:
        Graphics2D& graphics;
        Ghurund::UI::Direct2D::Canvas* canvas;
        RootView* rootView;
        Map<RenderTarget*, std::shared_ptr<RenderTarget2D>> renderTargets;
        IUIContext* context;
        ApplicationWindow& window;
        ConstraintGraph graph;

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
        UILayer(Graphics2D& graphics, ApplicationWindow& window, ResourceManager& resourceManager);

        ~UILayer() {
            rootView->release();
            delete canvas;
            delete context;
        }

        void initTargets();

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

        virtual void update(const uint64_t time) override;

        virtual Status draw(RenderTarget& renderTarget) override;
    };
}