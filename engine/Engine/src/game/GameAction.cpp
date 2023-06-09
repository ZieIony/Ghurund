#include "ghpch.h"

#include "GameAction.h"

namespace Ghurund {

    const GameAction GameAction::GO_FORWARD = GameAction(GameActionEnum::GO_FORWARD, "go forward");
    const GameAction GameAction::GO_BACKWARDS = GameAction(GameActionEnum::GO_BACKWARDS, "go backwards");
    const GameAction GameAction::STRAFE_LEFT = GameAction(GameActionEnum::STRAFE_LEFT, "strafe left");
    const GameAction GameAction::STRAFE_RIGHT = GameAction(GameActionEnum::STRAFE_RIGHT, "strafe right");
    const GameAction GameAction::FLOAT_UP = GameAction(GameActionEnum::FLOAT_UP, "float up");
    const GameAction GameAction::FLOAT_DOWN = GameAction(GameActionEnum::FLOAT_DOWN, "float down");
    const GameAction GameAction::RUN = GameAction(GameActionEnum::RUN, "run");
}