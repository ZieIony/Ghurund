#include "game/Target.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Target *Target_new() {
    return new Target();
}
