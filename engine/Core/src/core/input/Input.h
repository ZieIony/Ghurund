#pragma once

#include "core/collection/List.h"
#include "core/object/NotNull.h"
#include "core/window/WindowMessage.h"
#include "EventConsumer.h"
#include "keyboard/KeyState.h"
#include "mouse/MouseButtonState.h"
#include "gamepad/GamepadInput.h"

namespace Ghurund::Core {
    class Input {
    private:
        MouseButtonState mouseButtonLeft = {}, mouseButtonMiddle = {}, mouseButtonRight = {};
        IntPoint prevMousePos = {};
        Array<KeyState> keys = 256;
        List<WindowMessage> events;
        GamepadInput gamepadInput;

    public:
        inline void addWindowEvent(const WindowMessage& msg) {
            events.add(msg);
        }

        void dispatchWindowEvents(uint64_t time, EventConsumer& consumer);

        void dispatchMouseButtonDownEvents(uint64_t time, EventConsumer& consumer);

        void dispatchKeyDownEvents(uint64_t time, EventConsumer& consumer);

        void dispatchGamepadEvents(uint64_t time, EventConsumer& consumer);

        inline void releaseAllKeysAndButtons() {
            // TODO: send cancel events
            mouseButtonLeft.isDown = false;
            mouseButtonMiddle.isDown = false;
            mouseButtonRight.isDown = false;
            for (auto& key : keys)
                key.isDown = false;
            events.clear();
        };

        inline bool isShiftDown() {
            return keys[VK_SHIFT].isDown;
        }

        inline bool isControlDown() {
            return keys[VK_CONTROL].isDown;
        }
    };
}