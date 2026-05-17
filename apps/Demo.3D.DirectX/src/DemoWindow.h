#pragma once

#include "DemoApplication.h"

#include "engine/application/GameWindow.h"
#include "engine/3d/directx/DxGraphics3DContext.h"
#include "core/coroutine/CoroutineTask.h"
#include "engine/3d/World3D.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::Engine::_3D;
	using namespace Ghurund::Engine::_3D::DirectX;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

		SharedPointer<DxGraphics3DContext> context3d;
		Set<RenderGroup> renderGroups;
		World3D* world = nullptr;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer
		);

		~DemoWindow() {
			delete world;
		}

		void init();

		CoroutineTask<void> initScene();

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void update() override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}
