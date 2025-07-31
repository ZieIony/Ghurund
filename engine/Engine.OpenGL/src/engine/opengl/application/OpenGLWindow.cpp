#include "gheoglpch.h"

#include "OpenGLWindow.h"

#include "core/application/Application.h"
#include "core/application/LayerList.h"
#include "core/reflection/Property.h"
#include "core/reflection/TypeBuilder.h"
#include "engine/opengl/OpenGLDrawingContext.h"

#include <GL/glew.h>

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& OpenGLWindow::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<OpenGLWindow>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool OpenGLWindow::onSizeChangedEvent() {
        glViewport(0, 0, Size.Width, Size.Height);
        return __super::onSizeChangedEvent();
    }

    OpenGLWindow::OpenGLWindow(NotNull<Ghurund::Core::Application> app, WindowStyle style, NotNull<OGlRenderer> renderer):ApplicationWindow(app, style), renderer(&renderer) {}

    void OpenGLWindow::init() {
        renderingContext.init(Handle);
    }

    void OpenGLWindow::uninit() {
        renderingContext.uninit();
    }

    void OpenGLWindow::paint() {
        /*renderingContext.startFrame();
        Color clearColor = { 0xff1f1f1f };
        renderer->clear(&clearColor);
        OpenGLDrawingContext context;
        Layers.draw(context);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glFlush();
        renderingContext.finishFrame();

        PAINTSTRUCT ps;
        BeginPaint(Handle, &ps);
        EndPaint(Handle, &ps);*/
    }

}
