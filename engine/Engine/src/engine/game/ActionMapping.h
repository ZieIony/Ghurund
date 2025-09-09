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
        template<Derived<GameAction<float>> A>
        inline void add(const GamepadButton& gamepadButton, IntrusivePointer<A> action) {
            gamepadButtonActions.put(gamepadButton.Value, IntrusivePointer<GameAction<float>>(action.get()));
        }

        template<typename To, Derived<GameAction<To>> A>
        inline void add(
            const GamepadButton& gamepadButton,
            IntrusivePointer<A> action,
            std::function<To(float)> transformer
        ) {
            gamepadButtonActions.put(
                gamepadButton.Value,
                IntrusivePointer<GameAction<float>>(ghnew TransformedGameAction(action, transformer))
            );
        }

        inline void remove(const GamepadButton& gamepadButton) {
            gamepadButtonActions.remove(gamepadButton.Value);
        }

        template<Derived<GameAction<FloatPoint>> A>
        inline void add(GamepadStick gamepadStick, IntrusivePointer<A> action) {
            gamepadStickActions.put(gamepadStick, IntrusivePointer<GameAction<FloatPoint>>(action.get()));
        }

        template<typename To, Derived<GameAction<To>> A>
        inline void add(
            GamepadStick gamepadStick,
            IntrusivePointer<A> action,
            std::function<To(FloatPoint)> transformer
        ) {
            gamepadStickActions.put(
                gamepadStick,
                IntrusivePointer<GameAction<FloatPoint>>(ghnew TransformedGameAction(action, transformer))
            );
        }

        inline void remove(GamepadStick gamepadStick) {
            gamepadStickActions.remove(gamepadStick);
        }

        template<Derived<GameAction<float>> A>
        inline void add(uint8_t keyCode, IntrusivePointer<A> action) {
            keyActions.put(toupper(keyCode), IntrusivePointer<GameAction<float>>(action.get()));
        }

        template<typename To, Derived<GameAction<To>> A>
        inline void add(
            uint8_t keyCode,
            IntrusivePointer<A> action,
            std::function<To(float)> transformer
        ) {
            keyActions.put(
                toupper(keyCode),
                IntrusivePointer<GameAction<float>>(ghnew TransformedGameAction(action, transformer))
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