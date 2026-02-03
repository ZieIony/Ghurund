#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include "engine/2d/entity/Scene2D.h"
#include "engine/2d/physics/World2D.h"
#include <engine/graphics/Camera.h>

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::Engine::_2D;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

		Set<RenderGroup> renderGroups;
		IntrusivePointer<Scene2D> scene;
		SharedPointer<World2D> world;
		IntrusivePointer<Entity2D> captain, ground;
		IntrusivePointer<Camera> camera;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer
		);

		~DemoWindow() {
			captain.set(nullptr);
			ground.set(nullptr);
			camera.set(nullptr);
			scene.set(nullptr);
			world.set(nullptr);
		}

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void update() override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}