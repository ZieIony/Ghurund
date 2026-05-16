#include "gheoglpch.h"
#include "OglRenderingContext.h"

#include <gl/GL.h>

namespace Ghurund::Engine::OpenGL {
    void OglRenderingContext::onInit() {
        dc = GetDC(window.Handle);

        PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd), 1 };
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
    
    void OglRenderingContext::onUninit() {
        uninitRenderingContext();
    }

    void OglRenderingContext::uninitRenderingContext() {
        wglMakeCurrent(dc, nullptr);
        wglDeleteContext(renderContext);
        ReleaseDC(window.Handle, dc);
    }
    
    void OglRenderingContext::startFrame() {
        wglMakeCurrent(dc, renderContext);
    }
    
    void OglRenderingContext::finishFrame() {
        SwapBuffers(dc);
    }

    void OglRenderingContext::clear(const Color* color) {
        if (color) {
            glClearColor(color->R, color->G, color->B, color->A);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void OglRenderingContext::draw(Set<RenderGroup>& renderGroups, ParameterManager& parameterManager) {
        for (auto& group : renderGroups) {
            group.objects.sort([&](const DrawPacket& first, const DrawPacket& second) -> bool {
                return (first.Order - second.Order) * (int8_t)group.DrawGroup.DrawOrder > 0;
            });
            for (auto& packet : group.objects) {
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
    }

    void OglRenderingContext::setSize(Ghurund::Core::IntSize size) {
        glViewport(0, 0, size.Width, size.Height);
    }
}