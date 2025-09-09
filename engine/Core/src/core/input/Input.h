#pragma once

#include "core/collection/List.h"
#include "core/object/NotNull.h"
#include "core/window/WindowMessage.h"
#include "EventConsumer.h"
#include "gamepad/GamepadState.h"
#include "keyboard/KeyState.h"
#include "mouse/MouseButtonState.h"
#include "gamepad/GamepadButtonState.h"

namespace Ghurund::Core {

    class Input {
    private:
        MouseButtonState mouseButtonLeft = {}, mouseButtonMiddle = {}, mouseButtonRight = {};
        IntPoint prevMousePos = {};
        Array<KeyState> keys = 256;
        List<WindowMessage> events;
        Array<GamepadButtonState> gamepadButtonState = GamepadButton::VALUES.Size;

        static inline float shortToFloat(SHORT s) {
            return (((int16_t)s) + 32768) / (float)(32767 + 32768) * 2 - 1;
        }

    public:
        inline void addWindowEvent(const WindowMessage& msg) {
            events.add(msg);
        }

        void dispatchWindowEvents(uint64_t time, NotNull<EventConsumer> consumer);

        void dispatchMouseButtonDownEvents(uint64_t time, NotNull<EventConsumer> consumer);

        void dispatchKeyDownEvents(uint64_t time, NotNull<EventConsumer> consumer);

        void dispatchGamepadEvents(uint64_t time, NotNull<EventConsumer> consumer);

        void releaseAllKeysAndButtons() {
            throw NotImplementedException();
        };

        inline bool isShiftDown() {
            return keys[VK_SHIFT].isDown;
        }

        inline bool isControlDown() {
            return keys[VK_CONTROL].isDown;
        }

        uint8_t getMaxGamepads() const;

        __declspec(property(get = getMaxGamepads)) uint8_t MaxGamepads;

        GamepadState* getGamepadState(uint8_t index);

        __declspec(property(get = getIsEnabled, put = setIsEnabled)) bool IsEnabled;
    };
}