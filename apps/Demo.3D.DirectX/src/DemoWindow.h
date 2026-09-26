#pragma once

#include "DemoApplication.h"

#include "engine/application/GameWindow.h"
#include "core/coroutine/CoroutineTask.h"
#include "engine/3d/World3D.h"
#include "engine/3d/scene/camera/CameraController.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::Engine::_3D;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

		Set<RenderGroup> renderGroups;
		World3D* world = nullptr;
		CameraController cameraController;

	protected:
		virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override {
			return cameraController.dispatchMouseButtonEvent(event);
		}

		virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override {
			return cameraController.dispatchMouseMotionEvent(event);
		}

		virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override {
			return cameraController.dispatchMouseWheelEvent(event);
		}

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

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

		virtual void update() override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}
