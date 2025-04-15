#pragma once

#include "engine/opengl/application/OpenGLWindow.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoApplication;

	class DemoWindow:public Ghurund::Engine::OpenGL::OpenGLWindow {
	private:
		DemoApplication& app;

	public:
		DemoWindow(DemoApplication& app, Ghurund::Engine::OpenGL::Renderer& renderer);

		virtual void init() override;
	};
}