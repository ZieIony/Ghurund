#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/game/action/ActionMapping.h"
#include <core/object/IntrusivePointer.h>

#include "TestGameAction.h"
#include <test/MemoryGuard.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Engine;
    using namespace UnitTest::Utils;

    TEST_CLASS(ActionMappingTest) {
    public:

        TEST_METHOD(ActionMapping_addGamepadButton) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestBoolAction>();
                mapping.add(0, GamepadButton::A, action.get());

                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::PRESSED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::STARTED == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::DOWN, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IN_PROGRESS == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::RELEASED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::FINISHED == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadButton_otherGamepad) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestBoolAction>();
                mapping.add(1, GamepadButton::A, action.get());

                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::PRESSED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::DOWN, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::RELEASED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadButton_otherButton) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestBoolAction>();
                mapping.add(0, GamepadButton::B, action.get());

                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::PRESSED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::DOWN, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::RELEASED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadButton_transformer) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestFloatAction>();
                mapping.add<float>(0, GamepadButton::A, action.get(), [](bool value) { return value ? 1.0f : 0.0f; });

                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::PRESSED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::STARTED == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::DOWN, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IN_PROGRESS == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::RELEASED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::FINISHED == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadTrigger) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestFloatAction>();
                mapping.add(0, GamepadTrigger::LEFT, action.get());

                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::LEFT, 0.5f, 0));
                Assert::IsTrue(TestActionState::STARTED == action->state);
                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::LEFT, 1.0f, 0));
                Assert::IsTrue(TestActionState::IN_PROGRESS == action->state);
                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::LEFT, 0.0f, 0));
                Assert::IsTrue(TestActionState::FINISHED == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadTrigger_buttonEvents) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestFloatAction>();
                mapping.add(0, GamepadTrigger::LEFT, action.get());

                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::PRESSED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::DOWN, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadButtonEvent(GamepadButtonEventArgs(0, GamepadButtonAction::RELEASED, GamepadButton::A, 0, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadTrigger_otherTrigger) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestFloatAction>();
                mapping.add(0, GamepadTrigger::LEFT, action.get());

                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::RIGHT, 0.5f, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::RIGHT, 1.0f, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::RIGHT, 0.0f, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadTrigger_triggerPressedLightly) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestFloatAction>();
                mapping.add(0, GamepadTrigger::LEFT, action.get());

                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::LEFT, 0.0f, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::LEFT, 0.001f, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
                mapping.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(0, GamepadTrigger::LEFT, 0.0f, 0));
                Assert::IsTrue(TestActionState::IDLE == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addGamepadStick) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestFloatPointAction>();
                mapping.add(0, GamepadStick::LEFT, action.get());

                mapping.dispatchGamepadStickEvent(GamepadStickEventArgs(0, GamepadStick::LEFT, { 0.5f, 0.0f }, 0));
                Assert::IsTrue(TestActionState::STARTED == action->state);
                mapping.dispatchGamepadStickEvent(GamepadStickEventArgs(0, GamepadStick::LEFT, { 0.5f, 0.0f }, 0));
                Assert::IsTrue(TestActionState::IN_PROGRESS == action->state);
                mapping.dispatchGamepadStickEvent(GamepadStickEventArgs(0, GamepadStick::LEFT, { 0.0f, 0.0f }, 0));
                Assert::IsTrue(TestActionState::FINISHED == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addKey) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestBoolAction>();
                mapping.add('a', action.get());

                mapping.dispatchKeyEvent(KeyEventArgs(KeyAction::PRESSED, 'a', 0, 0));
                Assert::IsTrue(TestActionState::STARTED == action->state);
                mapping.dispatchKeyEvent(KeyEventArgs(KeyAction::DOWN, 'a', 0, 0));
                Assert::IsTrue(TestActionState::IN_PROGRESS == action->state);
                mapping.dispatchKeyEvent(KeyEventArgs(KeyAction::RELEASED, 'a', 0, 0));
                Assert::IsTrue(TestActionState::FINISHED == action->state);
            }
        }

        TEST_METHOD(ActionMapping_addMouseButton) {
            MemoryGuard guard;
            {
                ActionMapping mapping;
                auto action = makeIntrusive<TestBoolAction>();
                mapping.add(MouseButton::LEFT, action.get());

                mapping.dispatchMouseButtonEvent(MouseButtonEventArgs({ 0, 0 }, MouseButtonAction::PRESSED, MouseButton::LEFT, 0, 0, true));
                Assert::IsTrue(TestActionState::STARTED == action->state);
                mapping.dispatchMouseButtonEvent(MouseButtonEventArgs({ 0, 0 }, MouseButtonAction::DOWN, MouseButton::LEFT, 0, 0, true));
                Assert::IsTrue(TestActionState::IN_PROGRESS == action->state);
                mapping.dispatchMouseButtonEvent(MouseButtonEventArgs({ 0, 0 }, MouseButtonAction::RELEASED, MouseButton::LEFT, 0, 0, true));
                Assert::IsTrue(TestActionState::FINISHED == action->state);
            }
        }
    };
}
