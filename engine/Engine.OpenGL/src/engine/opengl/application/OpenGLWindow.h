#pragma once

#include "core/application/ApplicationWindow.h"
#include "core/window/SystemWindow.h"
#include "engine/opengl/OpenGLDrawingContext.h"
#include "engine/opengl/Renderer.h"

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    class OpenGLWindow: public Ghurund::Core::ApplicationWindow<OpenGLDrawingContext> {
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
        Renderer& renderer;
        HDC dc;
        HGLRC renderContext;

    protected:
        virtual bool onSizeChangedEvent() override {
            glViewport(0, 0, Size.Width, Size.Height);
            return __super::onSizeChangedEvent();
        }

    public:
        OpenGLWindow(Ghurund::Core::Application& app, Renderer& renderer);

        virtual void init() override;

        void uninit();

        virtual void paint() override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Core::LayerList<Ghurund::Engine::OpenGL::OpenGLDrawingContext>>();
}