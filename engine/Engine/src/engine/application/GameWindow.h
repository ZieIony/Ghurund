#pragma once

#include "core/application/Application.h"
#include "core/application/ApplicationWindow.h"
#include "engine/graphics/Renderer.h"

namespace Ghurund::Engine::DirectX {
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

    protected:
        virtual bool onSizeChangedEvent() override;

    public:
        GameWindow(NotNull<Ghurund::Core::Application> app, WindowStyle style):ApplicationWindow(app, style) {}

        Renderer* getRenderer() const {
            return renderer;
        }

        inline void setRenderer(Renderer* renderer) {
            this->renderer = renderer;
        }

        __declspec(property(get = getRenderer, put = setRenderer)) Renderer* Renderer;
    };
}
