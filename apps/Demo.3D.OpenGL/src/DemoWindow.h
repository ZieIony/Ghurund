#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include <engine/game/ActionMapping.h>

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class CloseWindowAction:public GameAction {
	private:
		Ghurund::Engine::GameWindow* window;

	public:
		CloseWindowAction(NotNull<Ghurund::Engine::GameWindow> window):window(&window) {}

		virtual void onFinished() override {
			window->Visible = false;
			window->Application->quit();
		}
	};

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;
		GameAction* closeWindow = nullptr;
		ActionMapping actionMapping;

	public:
		DemoWindow(NotNull<DemoApplication> app, NotNull<Ghurund::Engine::OpenGL::OglRenderer> renderer);

		virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& args) override;

		virtual bool onGamepadStickEvent(const GamepadStickEventArgs& args) override;
	
		virtual bool onKeyEvent(const KeyEventArgs& args) override;
	};
}