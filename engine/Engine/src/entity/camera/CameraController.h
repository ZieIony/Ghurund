#pragma once

#include "core/input/EventConsumer.h"
#include "core/input/Input.h"
#include "game/KeyMap.h"
#include "entity/camera/CameraEntity.h"

namespace Ghurund::Core {
    class SystemWindow;
}

namespace Ghurund {
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
        KeyMap keyMap;

    public:
        CameraController(CameraEntity& camera, SystemWindow* window = nullptr);

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        void update(Input& input, float dt);
    };
}