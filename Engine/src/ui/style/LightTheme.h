#pragma once

#include "BaseTheme.h"

namespace Ghurund::UI {
    class LightTheme:public BaseTheme {
    public:
        //static constexpr uint32_t color_error = 0xffCF6679;
        //static constexpr uint32_t color_onError = 0xff000000;
        uint32_t color_accent;
        static constexpr uint32_t color_accent_dark = 0xff005B99;
        static constexpr uint32_t color_background = 0xffffffff;
        static constexpr uint32_t color_foreground_onBackground = 0xff000000;
        static constexpr uint32_t color_foreground_onAccent = 0xffffffff;

        LightTheme(Ghurund::ResourceContext& context, uint32_t accent):BaseTheme(context), color_accent(accent) {
            Colors.set(COLOR_BACKGR0UND, color_background);
            Colors.set(COLOR_ACCENT, color_accent);
            Colors.set(COLOR_FOREGROUND_ONBACKGROUND, color_foreground_onBackground);
            Colors.set(COLOR_FOREGROUND_ONACCENT, color_foreground_onAccent);
            updateColors();
        }

    };
}