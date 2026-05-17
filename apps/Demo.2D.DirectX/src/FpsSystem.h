#pragma once

#include "engine/application/GameWindow.h"
#include "engine/game/system/System.h"

namespace Demo {
	using namespace Ghurund::Engine;

	class FpsSystem:public System {
	private:
		GameWindow& window;

	protected:
		virtual bool getUsesFixedUpdateInternal() const override {
			return false;
		}

	public:
		FpsSystem(GameWindow& window):window(window) {}

		virtual void update(const Timer& timer) override {
			auto text = std::format(_T("fps: {:.2f}"), timer.FramesPerSecond);
			window.Title = String(text.c_str());
		}
	};
}
