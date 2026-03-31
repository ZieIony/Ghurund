#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include "engine/2d/scene/Scene2D.h"
#include "engine/2d/physics/World2D.h"
#include "engine/2d/scene/camera/Camera2D.h"
#include <engine/2d/scene/Entity2D.h>
#include <engine/2d/scene/camera/CameraComponent2D.h>
#include <engine/2d/directx/DxGraphics2DContext.h>
#include <core/coroutine/CoroutineTask.h>
#include <engine/audio/sound/Sound.h>
#include "engine/2d/audio/AudioWorld2D.h"

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
		IntrusivePointer<Scene2D> scene;
		SharedPointer<World2D> world;
		SharedPointer<AudioWorld2D> audioWorld;
		IntrusivePointer<Entity2D> captain, ground;
		IntrusivePointer<Camera2D> camera;
		IntrusivePointer<CameraComponent2D> cameraComponent;
		float direction = 1;

		IntrusivePointer<Sound> thudSound;
		IntrusivePointer<AudioListenerComponent2D> audioListenerComponent;
		IntrusivePointer<SoundComponent2D> soundComponent;

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

		void init();

		CoroutineTask initScene();

		CoroutineTask initGround();

		CoroutineTask initCaptain();

		CoroutineTask jumpDelayed();

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void update() override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}
