#include "gheoglpch.h"

#include "OpenGLWindow.h"

#include "core/application/Application.h"
#include "core/application/LayerList.h"
#include "core/reflection/Property.h"
#include "core/reflection/TypeBuilder.h"
#include "engine/opengl/OpenGLDrawingContext.h"

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& OpenGLWindow::GET_TYPE() {
        static auto PROPERTY_APPLICATION = Property<OpenGLWindow, Ghurund::Core::Application&>("Application", &getApplication);

        static const Ghurund::Core::Type TYPE = TypeBuilder<OpenGLWindow>()
            .withProperty(PROPERTY_APPLICATION)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    OpenGLWindow::OpenGLWindow(Ghurund::Core::Application& app, Renderer& renderer):ApplicationWindow(app), renderer(renderer) {}

    void OpenGLWindow::init() {
        __super::init();

        PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd), 1 };
        if (!dc) {
            dc = GetDC(Handle);

            pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_COMPOSITION | PFD_DOUBLEBUFFER;
            pfd.iPixelType = PFD_TYPE_RGBA;
            pfd.cColorBits = 32;
            pfd.cAlphaBits = 8;
            pfd.iLayerType = PFD_MAIN_PLANE;
            auto format_index = ::ChoosePixelFormat(dc, &pfd);
            if (!format_index)
                throw CallFailedException();

            if (!::SetPixelFormat(dc, format_index, &pfd))
                throw CallFailedException();
        }

        auto active_format_index = ::GetPixelFormat(dc);
        if (!active_format_index)
            throw CallFailedException();

        if (!::DescribePixelFormat(dc, active_format_index, sizeof(pfd), &pfd))
            throw CallFailedException();

        if ((pfd.dwFlags & PFD_SUPPORT_OPENGL) != PFD_SUPPORT_OPENGL)
            throw CallFailedException();

        renderContext = wglCreateContext(dc);
        if (!renderContext)
            throw CallFailedException();
    }

    void OpenGLWindow::uninit() {
        wglMakeCurrent(dc, nullptr);
        wglDeleteContext(renderContext);
        ReleaseDC(Handle, dc);
        __super::uninit();
    }

    void OpenGLWindow::paint() {
        wglMakeCurrent(dc, renderContext);
        OpenGLDrawingContext context;
        Layers.draw(context);

        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glFlush();
        SwapBuffers(dc);

        PAINTSTRUCT ps;
        BeginPaint(Handle, &ps);
        EndPaint(Handle, &ps);
    }

}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Core::LayerList<Ghurund::Engine::OpenGL::OpenGLDrawingContext>>() {
        static Type TYPE = TypeBuilder<Ghurund::Core::LayerList<Ghurund::Engine::OpenGL::OpenGLDrawingContext>>();
        return TYPE;
    }
}