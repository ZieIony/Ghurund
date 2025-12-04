#pragma once

#include "GamepadButtonState.h"
#include "GamepadState.h"

#include "core/input/EventConsumer.h"

namespace Ghurund::Core {
    class GamepadInput {
    private:
        Array<GamepadButtonState> gamepadButtonState = GamepadButton::VALUES.Size;

        static inline float shortToFloat(SHORT s) {
            return (((int16_t)s) + 32768) / (float)(32767 + 32768) * 2 - 1;
        }

        GamepadState* getGamepadState(uint8_t index);

    public:
        static const uint8_t MAX_GAMEPADS;

        void dispatchEvents(uint64_t time, EventConsumer& consumer);
    };
}