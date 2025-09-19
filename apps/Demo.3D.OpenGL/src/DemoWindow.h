#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;
		IntrusivePointer<GameAction<bool>> closeWindow;
		IntrusivePointer<GameAction<FloatPoint>> moveWindow;

	public:
		DemoWindow(NotNull<DemoApplication> app, NotNull<Ghurund::Engine::OpenGL::OglRenderer> renderer);

		~DemoWindow();

		virtual bool onKeyEvent(const KeyEventArgs& args) override;
	};
}