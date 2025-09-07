#include "ghcpch.h"
#include "GamepadButton.h"

#include <xinput.h>

namespace Ghurund::Core {
    const GamepadButton GamepadButton::DPAD_UP = GamepadButton(GamepadButtonEnum::DPAD_UP, "DPAD_UP", XINPUT_GAMEPAD_DPAD_UP);
    const GamepadButton GamepadButton::DPAD_DOWN = GamepadButton(GamepadButtonEnum::DPAD_DOWN, "DPAD_DOWN", XINPUT_GAMEPAD_DPAD_DOWN);
    const GamepadButton GamepadButton::DPAD_LEFT = GamepadButton(GamepadButtonEnum::DPAD_LEFT, "DPAD_LEFT", XINPUT_GAMEPAD_DPAD_LEFT);
    const GamepadButton GamepadButton::DPAD_RIGHT = GamepadButton(GamepadButtonEnum::DPAD_RIGHT, "DPAD_RIGHT", XINPUT_GAMEPAD_DPAD_RIGHT);
    const GamepadButton GamepadButton::START = GamepadButton(GamepadButtonEnum::START, "START", XINPUT_GAMEPAD_START);
    const GamepadButton GamepadButton::BACK = GamepadButton(GamepadButtonEnum::BACK, "BACK", XINPUT_GAMEPAD_BACK);
    const GamepadButton GamepadButton::LEFT_STICK = GamepadButton(GamepadButtonEnum::LEFT_STICK, "LEFT_STICK", XINPUT_GAMEPAD_LEFT_THUMB);
    const GamepadButton GamepadButton::RIGHT_STICK = GamepadButton(GamepadButtonEnum::RIGHT_STICK, "RIGHT_STICK", XINPUT_GAMEPAD_RIGHT_THUMB);
    const GamepadButton GamepadButton::LEFT_SHOULDER = GamepadButton(GamepadButtonEnum::LEFT_SHOULDER, "LEFT_SHOULDER", XINPUT_GAMEPAD_LEFT_SHOULDER);
    const GamepadButton GamepadButton::RIGHT_SHOULDER = GamepadButton(GamepadButtonEnum::RIGHT_SHOULDER, "RIGHT_SHOULDER", XINPUT_GAMEPAD_RIGHT_SHOULDER);
    const GamepadButton GamepadButton::A = GamepadButton(GamepadButtonEnum::A, "A", XINPUT_GAMEPAD_A);
    const GamepadButton GamepadButton::B = GamepadButton(GamepadButtonEnum::B, "B", XINPUT_GAMEPAD_B);
    const GamepadButton GamepadButton::X = GamepadButton(GamepadButtonEnum::X, "X", XINPUT_GAMEPAD_X);
    const GamepadButton GamepadButton::Y = GamepadButton(GamepadButtonEnum::Y, "Y", XINPUT_GAMEPAD_Y);

    template<>
    const Type& getType<GamepadButton>() {
        static Type TYPE = Type(Ghurund::Core::NAMESPACE_NAME, "GamepadButton", sizeof(GamepadButton));
        return TYPE;
    }
}