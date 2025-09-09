#pragma once

#include "engine/application/GameWindow.h"
#include "engine/game/ActionMapping.h"

namespace Demo {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;

	class CloseWindowAction:public GameAction<float> {
	private:
		Ghurund::Engine::GameWindow* window;

		virtual void onFinished(uint64_t duration) override {
			window->Visible = false;
			window->Application->quit();
		}

	public:
		CloseWindowAction(NotNull<Ghurund::Engine::GameWindow> window):window(&window) {}
	};
}