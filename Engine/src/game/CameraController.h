#pragma once

#include "entity/Camera.h"
#include "input/EventConsumer.h"
#include "KeyMap.h"
#include "input/Input.h"

namespace Ghurund {
    class CameraController: public EventConsumer {
    public:
        enum class Mode {
            NONE, ORBIT, PAN, ZOOM, ROTATE
        };

    private:
        Camera& camera;
        Map<MouseButton, Mode> modeMap;
        bool pressed = false;
        MouseButton pressedButton = MouseButton::LEFT;
        float rotateSensivity = 1.0f / 5 * XM_PI / 180;
        static constexpr float DIST_EPSILON = 0.01f;
        Window* window;
        KeyMap keyMap;

    public:
        CameraController(Camera& camera, Window* window = nullptr):camera(camera) {
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

        virtual bool onMouseButtonEvent(MouseButtonEvent& event) override {
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

        virtual bool onMouseMouseMotionEvent(MouseMotionEvent& event) override {
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

        virtual bool onMouseWheelEvent(MouseWheelEvent& event) override {
            if (camera.getDistance() > event.Delta) {
                camera.zoom((float)event.Delta);
            } else {
                camera.zoom(camera.getDistance() - DIST_EPSILON);
            }
            return true;
        }

        void update(Input& input) {
            float vel = 5;
            if (input.Keys[keyMap[GameAction::RUN]])
                vel *= 3;
            if (input.Keys[keyMap[GameAction::GO_FORWARD]]) {
                camera.setPositionDirectionUp(XMFLOAT3(
                    camera.Position.x + camera.Direction.x * vel,
                    camera.Position.y,
                    camera.Position.z + camera.Direction.z * vel),
                    camera.Direction);
            }
            if (input.Keys[keyMap[GameAction::GO_BACKWARDS]]) {
                camera.setPositionDirectionUp(XMFLOAT3(
                    camera.Position.x - camera.Direction.x * vel,
                    camera.Position.y,
                    camera.Position.z - camera.Direction.z * vel),
                    camera.Direction);
            }
            if (input.Keys[keyMap[GameAction::STRAFE_LEFT]]) {
                camera.setPositionDirectionUp(XMFLOAT3(
                    camera.Position.x - camera.Right.x * vel,
                    camera.Position.y,
                    camera.Position.z - camera.Right.z * vel),
                    camera.Direction);
            }
            if (input.Keys[keyMap[GameAction::STRAFE_RIGHT]]) {
                camera.setPositionDirectionUp(XMFLOAT3(
                    camera.Position.x + camera.Right.x * vel,
                    camera.Position.y,
                    camera.Position.z + camera.Right.z * vel),
                    camera.Direction);
            }
            if (input.Keys[keyMap[GameAction::FLOAT_UP]]) {
                camera.setPositionDirectionUp(XMFLOAT3(
                    camera.Position.x,
                    camera.Position.y + camera.Up.y * vel,
                    camera.Position.z),
                    camera.Direction);
            }
            if (input.Keys[keyMap[GameAction::FLOAT_DOWN]]) {
                camera.setPositionDirectionUp(XMFLOAT3(
                    camera.Position.x,
                    camera.Position.y - camera.Up.y * vel,
                    camera.Position.z),
                    camera.Direction);
            }
        }
    };
}