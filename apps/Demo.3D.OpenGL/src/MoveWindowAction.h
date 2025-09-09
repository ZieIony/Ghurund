#pragma once

#include "engine/application/GameWindow.h"
#include "engine/game/ActionMapping.h"

namespace Demo {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;

	class MoveWindowAction:public GameAction<FloatPoint> {
	private:
		Ghurund::Engine::GameWindow* window;
		Ghurund::Core::Timer* timer;

		virtual void onInProgress(FloatPoint value, uint64_t duration) override {
			if (std::sqrtf(std::powf(value.x, 2.0f) + std::powf(value.y, 2.0f)) > 0.1f) {
				double dt = timer->FrameTime;
				auto v = value * dt * 1000;
				window->Position = window->Position + IntPoint{ (int32_t)v.x, -(int32_t)v.y };
			}
		}

	public:
		MoveWindowAction(
			NotNull<Ghurund::Engine::GameWindow> window,
			NotNull<Ghurund::Core::Timer> timer
		):
			window(&window),
			timer(&timer) {
		}
	};
}