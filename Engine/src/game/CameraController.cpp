#include "CameraController.h"
#include "application/SystemWindow.h"

namespace Ghurund {
	using namespace std;

	CameraController::CameraController(Camera& camera, SystemWindow* window) :camera(camera) {
		modeMap.set(Input::MouseButton::LEFT, Mode::ORBIT);
		modeMap.set(Input::MouseButton::MIDDLE, Mode::PAN);
		modeMap.set(Input::MouseButton::RIGHT, Mode::ROTATE);

		keyMap.map(GameAction::RUN, VK_SHIFT);
		keyMap.map(GameAction::GO_FORWARD, 'W');
		keyMap.map(GameAction::GO_BACKWARDS, 'S');
		keyMap.map(GameAction::STRAFE_LEFT, 'A');
		keyMap.map(GameAction::STRAFE_RIGHT, 'D');
		keyMap.map(GameAction::FLOAT_UP, VK_SPACE);
		keyMap.map(GameAction::FLOAT_DOWN, 'C');

		this->window = window;
	}

	bool CameraController::dispatchMouseButtonEvent(const Input::MouseButtonEventArgs& event) {
		if (event.Action == Input::MouseAction::DOWN) {
			pressed = true;
			pressedButton = event.Button;
			if (window != nullptr)
				SetCapture(window->Handle);
			return true;
		} else if (event.Action == Input::MouseAction::UP) {
			pressed = false;
			ReleaseCapture();
			return true;
		}

		return false;
	}

	bool CameraController::dispatchMouseMotionEvent(const Input::MouseMotionEventArgs& event) {
		if (pressed) {
			Mode mode = modeMap.get(pressedButton);
			if (mode == CameraController::Mode::ORBIT) {
				XMFLOAT3 rotation = camera.getRotation();
				camera.setOrbit(rotation.x + event.Delta.x * rotateSensivity, max(-89.0f / 180.0f * XM_PI, min(rotation.y - event.Delta.y * rotateSensivity, 89.0f / 180.0f * XM_PI)));
			} else if (mode == CameraController::Mode::PAN) {
				camera.pan((float)event.Delta.x, (float)event.Delta.y);
			} else if (mode == CameraController::Mode::ZOOM) {
				if (camera.getDistance() > event.Delta.y)
					camera.zoom((float)-event.Delta.y);
			} else {
				XMFLOAT3 rotation = camera.getRotation();
				camera.setRotation(rotation.x + event.Delta.x * rotateSensivity, max(-89.0f / 180.0f * XM_PI, min(rotation.y - event.Delta.y * rotateSensivity, 89.0f / 180.0f * XM_PI)));
			}
		}

		return pressed;
	}

	bool CameraController::dispatchMouseWheelEvent(const Input::MouseWheelEventArgs& event) {
		if (camera.getDistance() > event.Delta) {
			camera.zoom((float)event.Delta);
		} else {
			camera.zoom(camera.getDistance() - DIST_EPSILON);
		}
		return true;
	}

	void CameraController::update(Input::Input& input, float dt) {
		/*float vel = 25 * dt;
		if (input.Keys[keyMap[GameAction::RUN]])
			vel *= 5;
		if (input.Keys[keyMap[GameAction::GO_FORWARD]]) {
			camera.setPositionTargetUp(
				XMFLOAT3(camera.Position.x + camera.Direction.x * vel, camera.Position.y, camera.Position.z + camera.Direction.z * vel),
				XMFLOAT3(camera.Target.x + camera.Direction.x * vel, camera.Target.y, camera.Target.z + camera.Direction.z * vel));
		}
		if (input.Keys[keyMap[GameAction::GO_BACKWARDS]]) {
			camera.setPositionTargetUp(
				XMFLOAT3(camera.Position.x - camera.Direction.x * vel, camera.Position.y, camera.Position.z - camera.Direction.z * vel),
				XMFLOAT3(camera.Target.x - camera.Direction.x * vel, camera.Target.y, camera.Target.z - camera.Direction.z * vel));
		}
		if (input.Keys[keyMap[GameAction::STRAFE_LEFT]]) {
			camera.setPositionTargetUp(
				XMFLOAT3(camera.Position.x - camera.Right.x * vel, camera.Position.y, camera.Position.z - camera.Right.z * vel),
				XMFLOAT3(camera.Target.x - camera.Right.x * vel, camera.Target.y, camera.Target.z - camera.Right.z * vel));
		}
		if (input.Keys[keyMap[GameAction::STRAFE_RIGHT]]) {
			camera.setPositionTargetUp(
				XMFLOAT3(camera.Position.x + camera.Right.x * vel, camera.Position.y, camera.Position.z + camera.Right.z * vel),
				XMFLOAT3(camera.Target.x + camera.Right.x * vel, camera.Target.y, camera.Target.z + camera.Right.z * vel));
		}
		if (input.Keys[keyMap[GameAction::FLOAT_UP]]) {
			camera.setPositionTargetUp(
				XMFLOAT3(camera.Position.x, camera.Position.y + camera.Up.y * vel, camera.Position.z),
				XMFLOAT3(camera.Target.x, camera.Target.y + camera.Up.y * vel, camera.Target.z));
		}
		if (input.Keys[keyMap[GameAction::FLOAT_DOWN]]) {
			camera.setPositionTargetUp(
				XMFLOAT3(camera.Position.x, camera.Position.y - camera.Up.y * vel, camera.Position.z),
				XMFLOAT3(camera.Target.x, camera.Target.y - camera.Up.y * vel, camera.Target.z));
		}*/
	}
}