#pragma once

#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "engine/opengl/Renderer.h"
#include "engine/opengl/OpenGLDrawingContext.h"
#include "core/application/Application.h"

#include "core/application/LayerList.h"

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    class OpenGLWindow: public Ghurund::Core::SystemWindow {
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
        LayerList<OpenGLDrawingContext> layers;
        Application& app;
        Renderer& renderer;
        HDC dc;
        HGLRC renderContext;

    protected:
        virtual bool onSizeChangedEvent() override {
            layers.Size = Size;
            glViewport(0, 0, Size.Width, Size.Height);
            __super::onSizeChangedEvent();
            return true;
        }

        virtual bool onFocusedChangedEvent() override;

    public:
        OpenGLWindow(Application& app, Renderer& renderer);

        virtual void init(WindowManager& windowManager) override;

        void uninit();

        inline LayerList<OpenGLDrawingContext>& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList<OpenGLDrawingContext>& Layers;

        inline Application& getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Ghurund::Core::Application& Application;

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void update(const uint64_t time) override;

        virtual void paint() override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Core::LayerList<Ghurund::Engine::OpenGL::OpenGLDrawingContext>>();
}