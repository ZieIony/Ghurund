#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include "engine/2d/scene/Scene2D.h"
#include "engine/2d/directx/DxGraphics2DContext.h"
#include "core/coroutine/CoroutineTask.h"
#include "engine/2d/World2D.h"
#include "Captain.h"
#include <Ground.h>

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::Engine::_2D;
	using namespace Ghurund::Engine::_2D::DirectX;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

		SharedPointer<DxGraphics2DContext> context2d;
		Set<RenderGroup> renderGroups;
		World2D* world = nullptr;
		IntrusivePointer<Captain> captain;
		IntrusivePointer<Ground> ground;
		float direction = 1;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer
		);

		~DemoWindow() {
			captain.set(nullptr);
			ground.set(nullptr);
			delete world;
		}

		void init();

		CoroutineTask<void> initScene();

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void update() override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}
