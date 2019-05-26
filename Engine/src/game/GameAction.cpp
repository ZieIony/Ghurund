#include "GameAction.h"

namespace Ghurund {

    const GameAction GameAction::GO_FORWARD = GameAction(GameActionEnum::GO_FORWARD, _T("go forward"));
    const GameAction GameAction::GO_BACKWARDS = GameAction(GameActionEnum::GO_BACKWARDS, _T("go backwards"));
    const GameAction GameAction::STRAFE_LEFT = GameAction(GameActionEnum::STRAFE_LEFT, _T("strafe left"));
    const GameAction GameAction::STRAFE_RIGHT = GameAction(GameActionEnum::STRAFE_RIGHT, _T("strafe right"));
    const GameAction GameAction::FLOAT_UP = GameAction(GameActionEnum::FLOAT_UP, _T("float up"));
    const GameAction GameAction::FLOAT_DOWN = GameAction(GameActionEnum::FLOAT_DOWN, _T("float down"));
    const GameAction GameAction::RUN = GameAction(GameActionEnum::RUN, _T("run"));

    EnumValues<GameActionEnum, GameAction> GameAction::VALUES = {
        &GameAction::GO_FORWARD,
        &GameAction::GO_BACKWARDS,
        &GameAction::STRAFE_LEFT,
        &GameAction::STRAFE_RIGHT,
        &GameAction::FLOAT_UP,
        &GameAction::FLOAT_DOWN,
        &GameAction::RUN
    };
}