#pragma once

#include "engine/application/GameWindow.h"

namespace Demo {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;

	class MoveWindowAction:public GameAction<FloatPoint> {
	private:
		Ghurund::Engine::GameWindow& window;
		Ghurund::Core::Timer& timer;

		virtual void onInProgress(uint64_t duration) override {
			double dt = timer.FrameTime;
			auto v = Value * dt * 1000;
			window.Position = window.Position + IntPoint{ (int32_t)v.x, -(int32_t)v.y };
		}

	public:
		MoveWindowAction(
			Ghurund::Engine::GameWindow& window,
			Ghurund::Core::Timer& timer
		):GameAction(0.1f),
			window(window),
			timer(timer) {
			name = _T("Move Window");
		}
	};
}