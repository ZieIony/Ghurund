#pragma once

#include "SampleApplication.h"
#include "Captain.h"
#include <Ground.h>

#include "engine/application/GameWindow.h"
#include "core/coroutine/CoroutineTask.h"
#include "engine/2d/World2D.h"

namespace Sample {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::Engine::_2D;
	using namespace Ghurund::Engine::_2D::DirectX;

	class SampleWindow:public Ghurund::Engine::GameWindow {
	private:
		SampleApplication& app;

		Set<RenderGroup> renderGroups;
		World2D* world = nullptr;
		IntrusivePointer<Captain> captain;
		IntrusivePointer<Ground> ground;
		float direction = 1;

	public:
		SampleWindow(SampleApplication& app);

		~SampleWindow() {
			captain.set(nullptr);
			ground.set(nullptr);
			delete world;
		}

		void init();

		CoroutineTask<void> initScene();

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}
