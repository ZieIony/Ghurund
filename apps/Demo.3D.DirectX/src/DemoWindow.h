#pragma once

#include "engine/application/GameWindow.h"
#include "DemoApplication.h"
#include "core/window/DisplayManager.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

	public:
		DemoWindow(
			NotNull<DemoApplication> app,
			NotNull<Ghurund::Engine::DirectX::DxRenderer> renderer
		);

		virtual bool onKeyEvent(const KeyEventArgs& args) override;
	};
}