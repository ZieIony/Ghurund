#pragma once

#include "GameAction.h"
#include "collection/Map.h"

namespace Ghurund {

    class KeyMap {
    private:
        Map<GameActionEnum, int> keyMap;

    public:
        inline void map(const GameAction& action, int key) {
            keyMap.set(action.Value, key);
        }

        inline bool isMapped(const GameAction& action) const {
            return keyMap.contains(action.Value);
        }

        inline int get(const GameAction& action) const {
            return keyMap.get(action.Value);
        }

        inline int operator[](const GameAction& action) {
            return keyMap[action.Value];
        }

        inline const int operator[](const GameAction& action) const {
            return keyMap[action.Value];
        }
    };
}