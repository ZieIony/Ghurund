#pragma once

#include "core/application/ApplicationWindow.h"
#include "core/window/SystemWindow.h"
#include "engine/opengl/OpenGLDrawingContext.h"
#include "engine/opengl/OGlRenderer.h"
#include <engine/opengl/RenderingContext.h>

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    class OpenGLWindow: public Ghurund::Core::ApplicationWindow {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = OpenGLWindow::GET_TYPE();
#pragma endregion

    private:
        RenderingContext renderingContext;
        // borrowed
        OGlRenderer* renderer;

    protected:
        virtual bool onSizeChangedEvent() override;

    public:
        OpenGLWindow(NotNull<Ghurund::Core::Application> app, WindowStyle style, NotNull<OGlRenderer> renderer);

        void init();

        void uninit();

        virtual void paint() override;
    };
}
