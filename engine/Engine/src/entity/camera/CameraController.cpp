#include "ghpch.h"
#include "CameraController.h"

#include "core/window/SystemWindow.h"

#include <DirectXMath.h>
//#include <entt.hpp>

#include "Camera.h"
#include "CameraComponent.h"
#include "entity/TransformComponent.h"

namespace Ghurund {
	using namespace std;
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	CameraController::CameraController(CameraEntity& cameraEntity, SystemWindow* window) :cameraEntity(cameraEntity) {
		modeMap.put(MouseButton::LEFT, Mode::ORBIT);
		modeMap.put(MouseButton::MIDDLE, Mode::PAN);
		modeMap.put(MouseButton::RIGHT, Mode::ROTATE);

		keyMap.map(GameAction::RUN, VK_SHIFT);
		keyMap.map(GameAction::GO_FORWARD, 'W');
		keyMap.map(GameAction::GO_BACKWARDS, 'S');
		keyMap.map(GameAction::STRAFE_LEFT, 'A');
		keyMap.map(GameAction::STRAFE_RIGHT, 'D');
		keyMap.map(GameAction::FLOAT_UP, VK_SPACE);
		keyMap.map(GameAction::FLOAT_DOWN, 'C');

		this->window = window;
	}

	bool CameraController::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
		if (event.Action == MouseAction::DOWN) {
			pressed = true;
			pressedButton = event.Button;
			if (window != nullptr)
				SetCapture(window->Handle);
			return true;
		} else if (event.Action == MouseAction::UP) {
			pressed = false;
			ReleaseCapture();
			return true;
		}

		return false;
	}

	bool CameraController::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
		/*if (pressed) {
			Camera& camera = *cameraEntity.Components.get<CameraComponent>().camera;
			TransformComponent& transformComponent = cameraEntity.Components.get<TransformComponent>();
			Mode mode = modeMap.get(pressedButton);
			if (mode == CameraController::Mode::ORBIT) {
				XMFLOAT3 rotation = camera.getRotation();
				camera.setOrbit(transformComponent, rotation.x + event.Delta.x * rotateSensivity, max(-89.0f / 180.0f * XM_PI, min(rotation.y - event.Delta.y * rotateSensivity, 89.0f / 180.0f * XM_PI)));
			} else if (mode == CameraController::Mode::PAN) {
				camera.pan(transformComponent, (float)event.Delta.x, (float)event.Delta.y);
			} else if (mode == CameraController::Mode::ZOOM) {
				if (camera.getDistance() > event.Delta.y)
					camera.zoom(transformComponent, (float)-event.Delta.y);
			} else {
				XMFLOAT3 rotation = camera.getRotation();
				camera.setRotation(transformComponent, rotation.x + event.Delta.x * rotateSensivity, max(-89.0f / 180.0f * XM_PI, min(rotation.y - event.Delta.y * rotateSensivity, 89.0f / 180.0f * XM_PI)));
			}
		}*/

		return pressed;
	}

	bool CameraController::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
		/*Camera& camera = *cameraEntity.Components.get<CameraComponent>().camera;
		TransformComponent& transformComponent = cameraEntity.Components.get<TransformComponent>();
		if (camera.getDistance() > event.Delta) {
			camera.zoom(transformComponent, (float)event.Delta);
		} else {
			camera.zoom(transformComponent, camera.getDistance() - DIST_EPSILON);
		}*/
		return true;
	}

	void CameraController::update(Input& input, float dt) {
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