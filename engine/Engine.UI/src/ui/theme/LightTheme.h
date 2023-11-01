#pragma once

#include "BaseTheme.h"

namespace Ghurund::UI {
    class LightTheme:public BaseTheme {
    public:
        //static constexpr uint32_t color_error = 0xffCF6679;
        //static constexpr uint32_t color_onError = 0xff000000;
        const Color& color_accent;
        static constexpr uint32_t color_accent_dark = 0xff005B99;
        static constexpr uint32_t color_background = 0xffffffff;
        static constexpr uint32_t color_foreground_onBackground = 0xff000000;
        static constexpr uint32_t color_foreground_onAccent = 0xffffffff;

        LightTheme(Ghurund::Core::ResourceManager& resourceManager, Ghurund::UI::DrawableFactory& drawableFactory, const Color& accent = 0xff0078D7)
            :BaseTheme(resourceManager, drawableFactory), color_accent(accent)
        {
            Colors.put(COLOR_BACKGR0UND, color_background);
            Colors.put(COLOR_ACCENT, color_accent);
            Colors.put(COLOR_FOREGROUND_ONBACKGROUND, color_foreground_onBackground);
            Colors.put(COLOR_FOREGROUND_ONACCENT, color_foreground_onAccent);
            updateColors();
        }

    };
}