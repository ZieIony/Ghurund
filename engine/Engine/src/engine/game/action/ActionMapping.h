#pragma once

#include "TransformedGameActionDispatcher.h"
#include "BoolGameActionDispatcher.h"
#include "core/collection/Map.h"
#include "core/input/EventConsumer.h"
#include "core/input/gamepad/GamepadInput.h"
#include "core/reflection/StandardTypes.h"
#include "FloatGameActionDispatcher.h"
#include "FloatPointGameActionDispatcher.h"
#include <core/object/SharedPointer.h>
#include "IntPointGameActionDispatcher.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ActionMapping: public EventConsumer {
    private:
        struct GamepadActions {
            Map<GamepadButtonEnum, SharedPointer<BaseGameActionDispatcher<bool>>> buttonActions;
            Map<GamepadTrigger, SharedPointer<BaseGameActionDispatcher<float>>> triggerActions;
            Map<GamepadStick, SharedPointer<BaseGameActionDispatcher<FloatPoint>>> stickActions;

            inline void clear() {
                buttonActions.clear();
                triggerActions.clear();
                stickActions.clear();
            }
        };

        Array<GamepadActions> gamepadActions = GamepadInput::MAX_GAMEPADS;
        Map<uint8_t, SharedPointer<BaseGameActionDispatcher<bool>>> keyActions;
        Map<MouseButton, SharedPointer<BaseGameActionDispatcher<bool>>> mouseButtonActions;
        Map<MouseWheel, SharedPointer<BaseGameActionDispatcher<float>>> mouseWheelActions;
        GameActionDispatcher<IntPoint>* mouseMotionAction = nullptr;

    public:
        ~ActionMapping() {
            delete mouseMotionAction;
        }

#pragma region Gamepad
        inline void add(uint8_t gamepad, const GamepadButton& gamepadButton, NotNull<GameAction<bool>> action) {
            gamepadActions[gamepad].buttonActions.put(
                gamepadButton.Value,
                SharedPointer<BaseGameActionDispatcher<bool>>(ghnew GameActionDispatcher<bool>(&action))
            );
        }

        template<typename To, typename T>
        inline void add(
            uint8_t gamepad,
            const GamepadButton& gamepadButton,
            NotNull<GameAction<To>> action,
            T transformer
        ) {
            auto underlyingDispatcher = ghnew GameActionDispatcher<To>(&action);
            auto transformedDispatcher = ghnew TransformedGameActionDispatcher<bool, To, T>(underlyingDispatcher, transformer);
            gamepadActions[gamepad].buttonActions.put(
                gamepadButton.Value,
                SharedPointer<BaseGameActionDispatcher<bool>>(transformedDispatcher)
            );
        }

        inline void remove(uint8_t gamepad, const GamepadButton& gamepadButton) {
            gamepadActions[gamepad].buttonActions.remove(gamepadButton.Value);
        }

        inline void add(uint8_t gamepad, GamepadTrigger gamepadTrigger, NotNull<GameAction<float>> action) {
            gamepadActions[gamepad].triggerActions.put(
                gamepadTrigger,
                SharedPointer<BaseGameActionDispatcher<float>>(ghnew GameActionDispatcher<float>(&action))
            );
        }

        template<typename To, typename T>
        inline void add(
            uint8_t gamepad,
            GamepadTrigger gamepadTrigger,
            NotNull<GameAction<To>> action,
            T transformer
        ) {
            auto underlyingDispatcher = ghnew GameActionDispatcher<To>(&action);
            auto transformedDispatcher = ghnew TransformedGameActionDispatcher<float, To, T>(underlyingDispatcher, transformer);
            gamepadActions[gamepad].triggerActions.put(
                gamepadTrigger,
                SharedPointer<BaseGameActionDispatcher<float>>(transformedDispatcher)
            );
        }

        inline void remove(uint8_t gamepad, GamepadTrigger gamepadTrigger) {
            gamepadActions[gamepad].triggerActions.remove(gamepadTrigger);
        }

        inline void add(uint8_t gamepad, GamepadStick gamepadStick, NotNull<GameAction<FloatPoint>> action) {
            gamepadActions[gamepad].stickActions.put(
                gamepadStick,
                SharedPointer<BaseGameActionDispatcher<FloatPoint>>(ghnew GameActionDispatcher<FloatPoint>(&action))
            );
        }

        template<typename To, typename T>
        inline void add(
            uint8_t gamepad,
            GamepadStick gamepadStick,
            NotNull<GameAction<To>> action,
            T transformer
        ) {
            auto underlyingDispatcher = ghnew GameActionDispatcher(&action);
            auto transformedDispatcher = ghnew TransformedGameActionDispatcher<FloatPoint, To, T>(underlyingDispatcher, transformer);
            gamepadActions[gamepad].stickActions.put(
                gamepadStick,
                SharedPointer<GameActionDispatcher<FloatPoint>>(transformedDispatcher)
            );
        }

        inline void remove(uint8_t gamepad, GamepadStick gamepadStick) {
            gamepadActions[gamepad].stickActions.remove(gamepadStick);
        }

        virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& event) override;

        virtual bool onGamepadTriggerEvent(const GamepadTriggerEventArgs& event) override;

        virtual bool onGamepadStickEvent(const GamepadStickEventArgs& args) override;
#pragma endregion

#pragma region keyboard
        inline void add(uint8_t keyCode, NotNull<GameAction<bool>> action) {
            keyActions.put(
                toupper(keyCode),
                SharedPointer<BaseGameActionDispatcher<bool>>(ghnew GameActionDispatcher<bool>(&action))
            );
        }

        template<typename To, typename T>
        inline void add(
            uint8_t keyCode,
            NotNull<GameAction<To>> action,
            T transformer
        ) {
            auto underlyingDispatcher = ghnew GameActionDispatcher<To>(&action);
            auto transformedDispatcher = ghnew TransformedGameActionDispatcher<bool, To, T>(underlyingDispatcher, transformer);
            keyActions.put(
                toupper(keyCode),
                SharedPointer<BaseGameActionDispatcher<bool>>(transformedDispatcher)
            );
        }

        inline void remove(uint8_t keyCode) {
            keyActions.remove(keyCode);
        }

        virtual bool onKeyEvent(const KeyEventArgs& event) override;
#pragma endregion

#pragma region mouse
        inline void add(MouseButton mouseButton, NotNull<GameAction<bool>> action) {
            mouseButtonActions.put(
                mouseButton,
                SharedPointer<BaseGameActionDispatcher<bool>>(ghnew GameActionDispatcher<bool>(&action))
            );
        }

        template<typename To, typename T>
        inline void add(
            MouseButton mouseButton,
            NotNull<GameAction<To>> action,
            T transformer
        ) {
            mouseButtonActions.put(
                mouseButton,
                SharedPointer<BaseGameActionDispatcher<bool>>(ghnew TransformedGameActionDispatcher<bool, To, T>(ghnew GameActionDispatcher(&action), transformer))
            );
        }

        inline void remove(MouseButton mouseButton) {
            mouseButtonActions.remove(mouseButton);
        }

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override;

#pragma endregion

        void clear();
    };
}