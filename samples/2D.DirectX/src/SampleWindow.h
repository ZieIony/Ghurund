#pragma once

#include "SampleApplication.h"
#include "Captain.h"
#include <Ground.h>

#include "engine/application/GameWindow.h"
#include "core/coroutine/CoroutineTask.h"
#include "engine/2d/World2D.h"
#include <engine/2d/graphics/sprite/SpriteRenderingSystem.h>
#include <engine/2d/physics/visualization/VisualizatonRenderingSystem.h>

namespace Sample {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::Engine::_2D;
	using namespace Ghurund::Engine::_2D::DirectX;

	class SampleWindow:public Ghurund::Engine::GameWindow {
	private:
		SampleApplication& app;

		World2D* world = nullptr;
		IntrusivePointer<SpriteRenderingSystem> spriteRenderingSystem;
		IntrusivePointer<VisualizationRenderingSystem> visualizationRenderingSystem;

		Captain captain;
		Ground ground;
		float direction = 1;

	public:
		SampleWindow(SampleApplication& app);

		~SampleWindow() {
			delete world;
		}

		void init();

		CoroutineTask<void> initScene();

		virtual bool onKeyEvent(const KeyEventArgs& args) override;
	};
}
