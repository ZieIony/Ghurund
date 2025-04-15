#pragma once

#include "engine/directx/application/DirectXWindow.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoApplication;

	class DemoWindow:public Ghurund::Engine::DirectX::DirectXWindow {
	private:
		DemoApplication& app;

	public:
		DemoWindow(DemoApplication& app, Ghurund::Engine::DirectX::Renderer& renderer);

		virtual void init() override;
	};
}