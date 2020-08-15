#pragma once

#include "Canvas.h"

namespace Ghurund::UI {
    __interface Gui {
        void init();
        Canvas* makeCanvas(HWND handle);
    };
}