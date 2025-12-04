#pragma once

#include "GameActionCollection.h"

#include "core/input/gamepad/GamepadInput.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    template<typename K, typename V>
    class GamepadGameActionCollection {
    private:
        Array<GameActionCollection<K, V>> actions = GamepadInput::MAX_GAMEPADS;

        GamepadGameActionCollection& operator=(const GamepadGameActionCollection& other) = delete;
        GamepadGameActionCollection& operator=(GamepadGameActionCollection&& other) = delete;

    public:
        inline void put(uint8_t gamepad, const K& key, GameAction<V>& action, uint8_t priority = 0) {
            actions[gamepad].put(key, action, priority);
        }

        template<typename To, Callable<To, V> T>
        inline void put(
            uint8_t gamepad,
            const K& key,
            GameAction<To>& action,
            T transformer,
            uint8_t priority = 0
        ) {
            actions[gamepad].put(key, action, transformer, priority);
        }

        inline void remove(uint8_t gamepad, const K& key) {
            actions[gamepad].remove(key);
        }

        inline void clear() {
            for (size_t i = 0; i < actions.Size; i++)
                actions[i].clear();
        }

        inline void queryEventDispatch(uint8_t gamepad, const K& key, const V& value, uint64_t time, List<OwnedNotNull<BaseDispatchInputTask>>& tasks) {
            actions[gamepad].queryEventDispatch(key, value, time, tasks);
        }
    };
}