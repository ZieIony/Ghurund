#pragma once

#include "core/input/EventConsumer.h"
#include "core/input/Input.h"
#include "core/window/SystemWindow.h"
#include "Camera3D.h"

#include <DirectXMath.h>

namespace Ghurund::Engine::_3D {
	using namespace Ghurund::Core;

	class CameraController: public EventConsumer {
	public:
		enum class Mode {
			NONE, ORBIT, PAN, ZOOM, ROTATE
		};

	private:
		Camera3D* camera = nullptr;
		SystemWindow* window = nullptr;

		Map<MouseButton, Mode> modeMap;
		bool pressed = false;
		MouseButton pressedButton = MouseButton::LEFT;

	protected:
		virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

		virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override;

		virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override;

	public:
		float rotateSensivity = 1.0f / 5 * ::DirectX::XM_PI / 180;
		float zoomSensitivity = 0.01f;
		float zoomStep = 1.0f;

		CameraController();

		inline void setCamera(Camera3D* camera) {
			setPointer(this->camera, camera);
		}

		inline Camera3D* getCamera() const {
			return camera;
		}

		__declspec(property(get = getCamera, put = setCamera)) Camera3D* Camera;

		inline void setWindow(SystemWindow* window) {
			this->window = window;
		}

		inline SystemWindow* getWindow() const {
			return window;
		}

		__declspec(property(get = getWindow, put = setWindow)) SystemWindow* Window;

		void update(Input& input, float dt);
	};
}
