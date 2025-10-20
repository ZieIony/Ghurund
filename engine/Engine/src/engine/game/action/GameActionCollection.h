#pragma once

#include "core/collection/Map.h"
#include "core/object/NotNull.h"
#include "core/reflection/StandardTypes.h"
#include "TransformedGameActionDispatcher.h"
#include <core/input/gamepad/GamepadInput.h>
#include <core/object/OwnedNotNull.h>
#include <core/object/SharedPointer.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    template<typename K, typename V>
    class GameActionCollection {
    private:
        Map<K, SharedPointer<BaseGameActionDispatcher<V>>> actions;

        GameActionCollection& operator=(const GameActionCollection& other) = delete;
        GameActionCollection& operator=(GameActionCollection&& other) = delete;

    public:
        inline void put(const K& key, NotNull<GameAction<V>> action, uint8_t priority = 0) {
            auto dispatcher = ghnew GameActionDispatcher<V>(&action, priority);
            actions.put(key, SharedPointer<BaseGameActionDispatcher<V>>(dispatcher));
        }

        template<typename To, Callable<To, V> T>
		inline void put(const K& key, NotNull<GameAction<To>> action, T transformer, uint8_t priority = 0) {
            auto dispatcher = ghnew TransformedGameActionDispatcher<V, To, T>(&action, transformer, priority);
            actions.put(key, SharedPointer<BaseGameActionDispatcher<V>>(dispatcher));
        }

        inline void remove(const K& key) {
            auto it = actions.find(key);
            if (it != actions.end()) {
                it->value->cancelAction();
                actions.remove(key);
            }
        }

        inline void clear() {
            actions.clear();
        }

        inline void queryEventDispatch(const K& key, const V& value, uint64_t time, List<OwnedNotNull<BaseGameActionDispatchEventTask>>& tasks) {
            auto it = actions.find(key);
            if (it != actions.end()) {
                size_t index = tasks.find([&](auto& item) { return item->Action == it->value->Action; });
                if (index != tasks.Size) {
                    if (tasks[index]->priority < it->value->Priority) {
                        tasks[index]->cancel();
                        tasks[index] = it->value->makeDispatchEventTask(value, time);
                    }
                } else {
                    tasks.add(it->value->makeDispatchEventTask(value, time));
                }
            }
        }
    };
}