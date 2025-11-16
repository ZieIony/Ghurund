#pragma once

#include "core/input/EventConsumer.h"
#include "core/reflection/StandardTypes.h"
#include "GameActionCollection.h"
#include "DispatchInputTask.h"
#include <core/collection/List.h>
#include <core/collection/Set.h>
#include "GamepadGameActionCollection.h"
#include <core/input/keyboard/KeyboardKey.h>
#include <core/object/IntrusivePointer.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ActionMapping: public EventConsumer {
    private:
        Set<IntrusivePointer<BaseGameAction>> currentActions;
        List<OwnedNotNull<BaseDispatchInputTask>> dispatchTasks;

        BaseInputDispatcher<XMINT2>* mouseMotionAction = nullptr;

        ActionMapping& operator=(const ActionMapping& other) = delete;

    public:
        GamepadGameActionCollection<GamepadButton, bool> gamepadButtonActions;
        GamepadGameActionCollection<GamepadTrigger, float> gamepadTriggerActions;
        GamepadGameActionCollection<GamepadStick, XMFLOAT2> gamepadStickActions;
        GameActionCollection<KeyboardKey, bool> keyActions;
        GameActionCollection<MouseButton, bool> mouseButtonActions;
        GameActionCollection<MouseWheel, float> mouseWheelActions;

        ~ActionMapping() {
            cancelAll();
            delete mouseMotionAction;
        }

        virtual bool onGamepadButtonEvent(const GamepadButtonEventArgs& event) override;

        virtual bool onGamepadTriggerEvent(const GamepadTriggerEventArgs& event) override;

        virtual bool onGamepadStickEvent(const GamepadStickEventArgs& args) override;

        virtual bool onKeyEvent(const KeyEventArgs& event) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override;

        inline void executeDispatches() {
            for (auto& task : dispatchTasks) {
                task->execute();
                task->Action->addReference();
                if (task->Action->IsInProgress) {
                    currentActions.put(IntrusivePointer<BaseGameAction>(task->Action));
                } else {
                    currentActions.remove(IntrusivePointer<BaseGameAction>(task->Action));
                }
            }
            dispatchTasks.clear();
        }

        inline void cancelAll() {
            for (auto& action : currentActions)
                action->cancel();
            currentActions.clear();
        }

        void clear();
    };
}