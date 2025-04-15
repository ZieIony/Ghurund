#pragma once

#include <Windows.h>
#include <core/Exceptions.h>

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

	class RenderingContext {
    private:
        HWND handle;
        HDC dc = {};
        HGLRC renderContext;

	public:
		void init(HWND handle) {
            this->handle = handle;
            dc = GetDC(handle);

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

        void uninit() {
            wglMakeCurrent(dc, nullptr);
            wglDeleteContext(renderContext);
            ReleaseDC(handle, dc);
        }

        void startFrame() {
            wglMakeCurrent(dc, renderContext);
        }

        void finishFrame() {
            SwapBuffers(dc);
        }
	};
}