#pragma once

#include "graphics/entity/Camera.h"
#include "input/EventConsumer.h"
#include "KeyMap.h"
#include "input/Input.h"

namespace Ghurund {
    class CameraController: public Input::EventConsumer {
    public:
        enum class Mode {
            NONE, ORBIT, PAN, ZOOM, ROTATE
        };

    private:
        Camera& camera;
        Map<Input::MouseButton, Mode> modeMap;
        bool pressed = false;
        Input::MouseButton pressedButton = Input::MouseButton::LEFT;
        float rotateSensivity = 1.0f / 5 * XM_PI / 180;
        static constexpr float DIST_EPSILON = 0.01f;
        SystemWindow* window;
        KeyMap keyMap;

    public:
        CameraController(Camera& camera, SystemWindow* window = nullptr);

        virtual bool dispatchMouseButtonEvent(const Input::MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const Input::MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const Input::MouseWheelEventArgs& event) override;

        void update(Input::Input& input, float dt);
    };
}