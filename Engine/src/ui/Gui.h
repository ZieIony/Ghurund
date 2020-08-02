#pragma once

#include "Canvas.h"

namespace Ghurund {
    __interface Gui {
        void init();
        Canvas* makeCanvas(HWND handle);
        Paint* makePaint();
        Font* makeFont(const String& family, float size);
    };
}