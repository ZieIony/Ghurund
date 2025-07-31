#pragma once

#include "engine/directx/application/DirectXWindow.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoApplication;

	class DemoWindow:public Ghurund::Engine::DirectX::DirectXWindow {
	private:
		static const inline WindowStyle DEMO_WINDOW_STYLE = WindowStyle{
			.hasMinimizeButton = true,
			.hasMaximizeButton = true,
			.hasTitle = true,
			.borderStyle = WindowBorderStyle::RESIZE,
			.showOnTaskbar = true
		};

		DemoApplication& app;

	public:
		DemoWindow(DemoApplication& app, Ghurund::Engine::DirectX::DxRenderer& renderer);
	};
}