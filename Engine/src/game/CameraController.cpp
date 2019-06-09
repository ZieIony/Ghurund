#include "CameraController.h"

namespace Ghurund {
    CameraController::CameraController(Camera& camera, Window* window):camera(camera) {
        modeMap.set(MouseButton::LEFT, Mode::ORBIT);
        modeMap.set(MouseButton::MIDDLE, Mode::PAN);
        modeMap.set(MouseButton::RIGHT, Mode::ROTATE);

        keyMap.map(GameAction::RUN, VK_SHIFT);
        keyMap.map(GameAction::GO_FORWARD, 'W');
        keyMap.map(GameAction::GO_BACKWARDS, 'S');
        keyMap.map(GameAction::STRAFE_LEFT, 'A');
        keyMap.map(GameAction::STRAFE_RIGHT, 'D');
        keyMap.map(GameAction::FLOAT_UP, VK_SPACE);
        keyMap.map(GameAction::FLOAT_DOWN, 'C');

        this->window = window;
    }

    bool CameraController::onMouseButtonEvent(MouseButtonEvent& event) {
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

    bool CameraController::onMouseMouseMotionEvent(MouseMotionEvent& event) {
        if (pressed) {
            Mode mode = modeMap.get(pressedButton);
            if (mode == CameraController::Mode::ORBIT) {
                XMFLOAT3& rotation = camera.getRotation();
                camera.setOrbit(rotation.x + event.Delta.x * rotateSensivity, max(-89.0f / 180.0f * XM_PI, min(rotation.y - event.Delta.y * rotateSensivity, 89.0f / 180.0f * XM_PI)));
            } else if (mode == CameraController::Mode::PAN) {
                camera.pan((float)event.Delta.x, (float)event.Delta.y);
            } else if (mode == CameraController::Mode::ZOOM) {
                if (camera.getDistance() > event.Delta.y)
                    camera.zoom((float)-event.Delta.y);
            } else {
                XMFLOAT3& rotation = camera.getRotation();
                camera.setRotation(rotation.x + event.Delta.x * rotateSensivity, max(-89.0f / 180.0f * XM_PI, min(rotation.y - event.Delta.y * rotateSensivity, 89.0f / 180.0f * XM_PI)));
            }
        }

        return pressed;
    }

    bool CameraController::onMouseWheelEvent(MouseWheelEvent& event) {
        if (camera.getDistance() > event.Delta) {
            camera.zoom((float)event.Delta);
        } else {
            camera.zoom(camera.getDistance() - DIST_EPSILON);
        }
        return true;
    }

    void CameraController::update(Input& input) {
        float vel = 5;
        if (input.Keys[keyMap[GameAction::RUN]])
            vel *= 3;
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
        }
    }
}