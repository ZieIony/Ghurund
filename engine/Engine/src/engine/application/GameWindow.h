#pragma once

#include "core/application/Application.h"
#include "core/application/ApplicationWindow.h"
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
        std::unique_ptr<RenderingContext> renderingContext;

    protected:
        virtual bool onSizeChanged() override;

    public:
		static inline const WindowStyle DEFAULT_WINDOW_STYLE = WindowStyle{
            .hasMinimizeButton = true,
            .hasMaximizeButton = true,
            .hasTitle = true,
            .borderStyle = WindowBorderStyle::RESIZE,
            .showOnTaskbar = true
        };

		GameWindow(NotNull<Ghurund::Core::Application> app, WindowStyle style = DEFAULT_WINDOW_STYLE):ApplicationWindow(app, style) {}

        Renderer* getRenderer() const {
            return renderer;
        }

        inline void setRenderer(Renderer* renderer) {
            this->renderer = renderer;
            if (this->renderer) {
                renderingContext.reset(this->renderer->makeRenderingContext(*this));
                renderingContext->init();
            } else {
                renderingContext.reset();
            }
        }

        __declspec(property(get = getRenderer, put = setRenderer)) Renderer* Renderer;

        virtual void paint() override {
            if (!renderingContext)
                return;

            renderingContext->startFrame();
            renderingContext->clear(BackgroundColor);
            renderingContext->finishFrame();
        }
    };
}
