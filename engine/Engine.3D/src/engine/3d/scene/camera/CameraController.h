#pragma once

#include "core/input/EventConsumer.h"
#include "core/input/Input.h"
#include "core/window/SystemWindow.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class CameraEntity;

	class CameraController: public EventConsumer {
	public:
		enum class Mode {
			NONE, ORBIT, PAN, ZOOM, ROTATE
		};

	private:
		CameraEntity& cameraEntity;
		Map<MouseButton, Mode> modeMap;
		bool pressed = false;
		MouseButton pressedButton = MouseButton::LEFT;
		float rotateSensivity = 1.0f / 5 * ::DirectX::XM_PI / 180;
		static constexpr float DIST_EPSILON = 0.01f;
		SystemWindow* window;

		virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

		virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override;

		virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override;

	public:
		CameraController(CameraEntity& camera, SystemWindow* window = nullptr);

		void update(Input& input, float dt);
	};
}
