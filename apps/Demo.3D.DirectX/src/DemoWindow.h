#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include "engine/entity/Scene.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

		Set<RenderGroup> renderGroups;
		IntrusivePointer<Scene> scene;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer
		);

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void update(uint64_t time) override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}