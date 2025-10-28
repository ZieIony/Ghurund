#pragma once

#include "core/application/Application.h"
#include "core/application/ApplicationWindow.h"
#include "engine/game/action/ActionMapping.h"
#include "engine/graphics/Renderer.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class GameWindow: public Ghurund::Core::ApplicationWindow {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GameWindow::GET_TYPE();
#pragma endregion

    private:
        Renderer* renderer = nullptr;
        std::unique_ptr<RenderingContext> renderingContext = nullptr;
        ActionMapping actionMapping;

    protected:
        virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& event) override {
            return actionMapping.onGamepadButtonEvent(event);
        }

        virtual bool onGamepadStickEvent(const GamepadStickEventArgs& event) override {
            return actionMapping.onGamepadStickEvent(event);
        }

        virtual bool onGamepadTriggerEvent(const GamepadTriggerEventArgs& event) override {
            return actionMapping.onGamepadTriggerEvent(event);
        }

        virtual bool onKeyEvent(const KeyEventArgs& event) override {
            return __super::onKeyEvent(event) || actionMapping.onKeyEvent(event);
        }

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override {
            return __super::onMouseButtonEvent(event) || actionMapping.onMouseButtonEvent(event);
        }

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override {
            return __super::onMouseMotionEvent(event) || actionMapping.onMouseMotionEvent(event);
        }

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override {
            return __super::onMouseWheelEvent(event) || actionMapping.onMouseWheelEvent(event);
        }
        
        virtual bool onSizeChanged() override;

        virtual bool onFocusedChanged() override {
            if (!Focused)
                actionMapping.cancelAll();
            return __super::onFocusedChanged();
        }

        virtual void onPaint(RenderingContext& renderingContext) {}

    public:
		static inline const WindowStyle DEFAULT_WINDOW_STYLE = WindowStyle{
            .hasMinimizeButton = true,
            .hasMaximizeButton = true,
            .hasTitle = true,
            .borderStyle = WindowBorderStyle::RESIZE,
            .showOnTaskbar = true
        };

		GameWindow(Ghurund::Core::Application& app, WindowStyle style = DEFAULT_WINDOW_STYLE):ApplicationWindow(app, style) {}

        Renderer* getRenderer() const {
            return renderer;
        }

        inline void setRenderer(Renderer* renderer) {
            if (this->renderer == renderer)
                return;
            
            this->renderer = renderer;
            if (this->renderer) {
                renderingContext.reset(renderer->makeRenderingContext(*this));
                renderingContext->init();
            } else {
                renderingContext.reset();
            }
        }

        __declspec(property(get = getRenderer, put = setRenderer)) Renderer* Renderer;

        ActionMapping& getActionMapping() {
            return actionMapping;
        }

        __declspec(property(get = getActionMapping)) ActionMapping& ActionMapping;

        virtual void update(const uint64_t time) override;

        virtual void paint() override {
            if (!renderingContext)
                return;

            renderingContext->startFrame();
            renderingContext->clear(BackgroundColor);
            onPaint(*renderingContext);
            renderingContext->finishFrame();
        }
    };
}
