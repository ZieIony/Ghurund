#pragma once

#include "core/Enum.h"

namespace Ghurund {
    enum class GameActionEnum {
        GO_FORWARD, GO_BACKWARDS, STRAFE_LEFT, STRAFE_RIGHT, FLOAT_UP, FLOAT_DOWN, RUN
    };

    class GameAction:public Enum<GameActionEnum, GameAction> {
    public:
        static const GameAction GO_FORWARD, GO_BACKWARDS, STRAFE_LEFT, STRAFE_RIGHT, FLOAT_UP, FLOAT_DOWN, RUN;

        static const EnumValues<GameActionEnum, GameAction> VALUES;

        GameAction(GameActionEnum value, const tchar* name):Enum<GameActionEnum, GameAction>(value, name) {
        }
    };
}