#pragma once

#include "graphics/entity/Camera.h"
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
        CameraController(Camera& camera, Window* window = nullptr);

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        void update(Input& input, float dt);
    };
}