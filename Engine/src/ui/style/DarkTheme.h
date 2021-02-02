#pragma once

#include "DefaultTheme.h"

namespace Ghurund::UI {
    class DarkTheme:public DefaultTheme {
    public:
        static constexpr uint32_t color_error = 0xffCF6679;
        static constexpr uint32_t color_onBackground = 0xffFFFFFF;
        static constexpr uint32_t color_onError = 0xff000000;
        static constexpr uint32_t color_onAccent = 0xffffffff;
        uint32_t color_accent;
        static constexpr uint32_t color_accent_dark = 0xff005B99;
        static constexpr uint32_t color_background = 0xff121212;
        static constexpr uint32_t color_control = 0xffffffff;

        DarkTheme(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context, uint32_t accent):DefaultTheme(resourceManager, context), color_accent(accent) {
            Colors.set(COLOR_ERROR, color_error);
            Colors.set(COLOR_BACKGR0UND, color_background);
            Colors.set(COLOR_CONTROL, color_control);
            Colors.set(COLOR_ACCENT, color_accent);
            Colors.set(COLOR_ON_ERROR, color_onError);
            Colors.set(COLOR_ON_BACKGR0UND, color_onBackground);
            Colors.set(COLOR_ON_ACCENT, color_onAccent);
        }
    };
}