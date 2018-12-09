#pragma once

#include "entity/Camera.h"
#include "input/EventConsumer.h"

namespace Ghurund {
    class CameraController: public EventConsumer {
    public:
        enum class Mode {
            NONE, ORBIT, PAN, ZOOM, ROTATE
        };

    private:
        Camera &camera;
        Map<MouseButton, Mode> modeMap;
        bool pressed = false;
        MouseButton pressedButton = MouseButton::LEFT;
        float rotateSensivity = 1.0f/5*XM_PI/180;
        Window *window;

    public:
        CameraController(Camera &camera, Window *window = nullptr):camera(camera) {
            modeMap.set(MouseButton::LEFT, Mode::ORBIT);
            modeMap.set(MouseButton::MIDDLE, Mode::PAN);
            modeMap.set(MouseButton::RIGHT, Mode::ROTATE);
            this->window = window;
        }

        virtual bool onMouseButtonEvent(MouseButtonEvent &event) {
            if(event.Action==MouseAction::DOWN) {
                pressed = true;
                pressedButton = event.Button;
                if(window!=nullptr)
                    SetCapture(window->Handle);
                return true;
            } else if(event.Action==MouseAction::UP) {
                pressed = false;
                ReleaseCapture();
                return true;
            }

            return false;
        }

        virtual bool onMouseMouseMotionEvent(MouseMotionEvent &event) {
            if(pressed) {
                Mode mode = modeMap.get(pressedButton);
                if(mode==CameraController::Mode::ORBIT) {
                    XMFLOAT3 &rotation = camera.getRotation();
                    camera.setOrbit(rotation.x+event.Delta.x * rotateSensivity, max(-89.0f/180.0f*XM_PI, min(rotation.y-event.Delta.y * rotateSensivity, 89.0f/180.0f*XM_PI)));
                } else if(mode==CameraController::Mode::PAN) {
                    camera.pan((float)event.Delta.x, (float)event.Delta.y);
                } else if(mode==CameraController::Mode::ZOOM) {
                    if(camera.getDistance()>event.Delta.y)
                        camera.zoom((float)-event.Delta.y);
                } else {
                    XMFLOAT3 &rotation = camera.getRotation();
                    camera.setRotation(rotation.x+event.Delta.x * rotateSensivity, max(-89.0f/180.0f*XM_PI, min(rotation.y-event.Delta.y * rotateSensivity, 89.0f/180.0f*XM_PI)));
                }
            }

            return pressed;
        }

        virtual bool onMouseWheelEvent(MouseWheelEvent &event) {
            if(camera.getDistance()>event.Delta)
                camera.zoom((float)event.Delta);
            return true;
        }

        void setMode(MouseButton button, CameraController::Mode mode) {
            this->modeMap.set(button, mode);
        }

        CameraController::Mode getMode(MouseButton button) {
            return modeMap.get(button);
        }
    };
}