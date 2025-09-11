#pragma once

#include "TransformedGameAction.h"

#include "core/collection/Map.h"
#include "core/input/EventConsumer.h"
#include "core/object/IntrusivePointer.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ActionMapping: public EventConsumer {
    private:
        Map<uint8_t, IntrusivePointer<GameAction<float>>> keyActions;
        Map<GamepadButtonEnum, IntrusivePointer<GameAction<float>>> gamepadButtonActions;
        Map<GamepadStick, IntrusivePointer<GameAction<FloatPoint>>> gamepadStickActions;

    public:
        inline void add(const GamepadButton& gamepadButton, IntrusivePointer<GameAction<float>> action) {
            gamepadButtonActions.put(gamepadButton.Value, action);
        }

        template<typename To, typename T>
        inline void add(
            const GamepadButton& gamepadButton,
            IntrusivePointer<GameAction<To>> action,
            T transformer
        ) {
            gamepadButtonActions.put(
                gamepadButton.Value,
                makeIntrusive<TransformedGameAction<float, To, T>>(action, transformer)
            );
        }

        inline void remove(const GamepadButton& gamepadButton) {
            gamepadButtonActions.remove(gamepadButton.Value);
        }

        inline void add(GamepadStick gamepadStick, IntrusivePointer<GameAction<FloatPoint>> action) {
            gamepadStickActions.put(gamepadStick, action);
        }

        template<typename To, typename T>
        inline void add(
            GamepadStick gamepadStick,
            IntrusivePointer<GameAction<To>> action,
            T transformer
        ) {
            gamepadStickActions.put(
                gamepadStick,
                makeIntrusive<TransformedGameAction<float, To, T>>(action, transformer)
            );
        }

        inline void remove(GamepadStick gamepadStick) {
            gamepadStickActions.remove(gamepadStick);
        }

        inline void add(uint8_t keyCode, IntrusivePointer<GameAction<float>> action) {
            keyActions.put(toupper(keyCode), action);
        }

        template<typename To, typename T>
        inline void add(
            uint8_t keyCode,
            IntrusivePointer<GameAction<To>> action,
            T transformer
        ) {
            keyActions.put(
                toupper(keyCode),
                makeIntrusive<TransformedGameAction<float, To, T>>(action, transformer)
            );
        }

        inline void remove(uint8_t keyCode) {
            keyActions.remove(keyCode);
        }

        inline void clear() {
            gamepadButtonActions.clear();
            gamepadStickActions.clear();
            keyActions.clear();
        }

        virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& event) override;

        virtual bool onGamepadStickEvent(const GamepadStickEventArgs& args) override;

        virtual bool onKeyEvent(const KeyEventArgs& event) override;
    };
}