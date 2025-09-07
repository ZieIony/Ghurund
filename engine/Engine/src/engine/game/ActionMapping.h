#pragma once

#include "GameAction.h"
#include "core/collection/Map.h"
#include "core/input/EventConsumer.h"
#include "core/input/Keyboard.h"
#include "core/object/SharedPointer.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ActionMapping: public EventConsumer {
    private:
        Map<uint8_t, SharedPointer<GameAction>> keyActions;
        Map<GamepadButtonEnum, SharedPointer<GameAction>> gamepadButtonActions;

    public:
        void add(const GamepadButton& gamepadButton, SharedPointer<GameAction> action) {
            gamepadButtonActions.put(gamepadButton.Value, action);
        }

        void add(uint8_t keyCode, SharedPointer<GameAction> action) {
            keyActions.put(keyCode, action);
        }

        virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& event) {
            auto it = gamepadButtonActions.find(event.Button.Value);
            if (it != gamepadButtonActions.end()) {
                if (event.Action == GamepadButtonAction::PRESSED) {
                    it->value->dispatchStarted();
                } else if (event.Action == GamepadButtonAction::DOWN) {
                    it->value->dispatchInProgress();
                } else if (event.Action == GamepadButtonAction::RELEASED) {
                    it->value->dispatchFinished();
                }
                return true;
            }
            return false;
        }

        virtual bool onKeyEvent(const KeyEventArgs& event) {
            auto it = keyActions.find(event.KeyCode);
            if (it != keyActions.end()) {
                if (event.Action == KeyAction::PRESSED) {
                    it->value->dispatchStarted();
                } else if (event.Action == KeyAction::DOWN) {
                    it->value->dispatchInProgress();
                } else if (event.Action == KeyAction::RELEASED) {
                    it->value->dispatchFinished();
                }
                return true;
            }
            return false;
        }
    };
}