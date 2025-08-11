#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

	public:
		DemoWindow(NotNull<DemoApplication> app, NotNull<Ghurund::Engine::OpenGL::OGlRenderer> renderer);
	};
}