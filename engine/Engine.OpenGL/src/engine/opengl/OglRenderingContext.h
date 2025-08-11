#pragma once

#include "engine/graphics/RenderingContext.h"

#include <Windows.h>

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

	class OglRenderingContext: public Ghurund::Engine::RenderingContext {
    private:
        HDC dc = {};
        HGLRC renderContext = {};

	public:
        OglRenderingContext(NotNull<SystemWindow> window):Ghurund::Engine::RenderingContext(window) {}

		virtual void init() override;

        virtual void uninit() override;

        virtual void startFrame() override;

        virtual void finishFrame() override;
		
		virtual void clear(const Color* color) override;

		void draw() {
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

        virtual void setSize(Ghurund::Core::IntSize size) override;
	};
}