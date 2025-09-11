#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include "CloseWindowAction.h"
#include "MoveWindowAction.h"
#include "core/reflection/StandardTypes.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;
		IntrusivePointer<CloseWindowAction> closeWindow;
		IntrusivePointer<GameAction<FloatPoint>> moveWindow;
		ActionMapping actionMapping;

	public:
		DemoWindow(NotNull<DemoApplication> app, NotNull<Ghurund::Engine::OpenGL::OglRenderer> renderer);

		~DemoWindow();

		virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& args) override;

		virtual bool onGamepadStickEvent(const GamepadStickEventArgs& args) override;
	
		virtual bool onKeyEvent(const KeyEventArgs& args) override;
	};
}