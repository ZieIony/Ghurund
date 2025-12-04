#pragma once

#include "LayerList.h"

#include "core/application/Application.h"
#include "core/application/ApplicationWindow.h"
#include "engine/game/action/ActionMapping.h"
#include "engine/graphics/Renderer.h"
#include "engine/parameter/ParameterManager.h"
#include "engine/parameter/ValueParameter.h"

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
        ParameterManager parameterManager;
        LayerList layers;
        Renderer* renderer = nullptr;
        std::unique_ptr<RenderingContext> renderingContext = nullptr;
        ActionMapping actionMapping;

        IntrusivePointer<Int2Parameter> viewportSizeParameter;
        IntrusivePointer<FloatParameter> timeParameter;
        IntrusivePointer<Int2Parameter> mousePosParameter;

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

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override {
            mousePosParameter->Value = { event.Position.x, event.Position.y };
            return __super::onMouseMotionEvent(event) || actionMapping.onMouseMotionEvent(event);
        }

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override {
            return __super::onMouseWheelEvent(event) || actionMapping.onMouseWheelEvent(event);
        }
        
        virtual bool onSizeChanged() override;

        virtual bool onFocusedChanged() override;

        virtual void onPaint(RenderingContext& renderingContext) {}

    public:
		GameWindow(Ghurund::Core::Application& app, WindowStyle style = SystemWindow::DEFAULT_WINDOW_STYLE):ApplicationWindow(app, style) {
            viewportSizeParameter = makeIntrusive<Int2Parameter>("viewportSize");
            parameterManager.Parameters.put(viewportSizeParameter.get());
            timeParameter = makeIntrusive<FloatParameter>("time");
            parameterManager.Parameters.put(timeParameter.get());
            mousePosParameter = makeIntrusive<Int2Parameter>("mousePos");
            ParameterManager.Parameters.put(mousePosParameter.get());
        }

        inline LayerList& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList& Layers;

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

        ParameterManager& getParameterManager() {
            return parameterManager;
        }

        __declspec(property(get = getParameterManager)) ParameterManager& ParameterManager;

        virtual void update(const uint64_t time) override;

        virtual void paint() override {
            if (!renderingContext)
                return;

            renderingContext->startFrame();
            renderingContext->clear(BackgroundColor);
            __super::paint();
            onPaint(*renderingContext);
            layers.draw(*renderingContext, parameterManager);
            renderingContext->finishFrame();
        }
    };
}
