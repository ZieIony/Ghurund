#pragma once

#include "DefaultTheme.h"

namespace Ghurund::UI {
    class LightTheme:public DefaultTheme {
    public:
        static constexpr uint32_t color_error = 0xffB00020;
        static constexpr uint32_t color_onBackground = 0xff000000;
        static constexpr uint32_t color_onError = 0xffFFFFFF;
        static constexpr uint32_t color_onAccent = 0xffffffff;
        uint32_t color_accent;
        static constexpr uint32_t color_accent_dark = 0xff005B99;
        static constexpr uint32_t color_background = 0xffFFFFFF;
        static constexpr uint32_t color_control = 0xff000000;

        LightTheme(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context, uint32_t accent):DefaultTheme(resourceManager, context), color_accent(accent) {}

        virtual uint32_t getColorError() const {
            return color_error;
        }
        virtual uint32_t getColorBackground() const {
            return color_background;
        }
        virtual uint32_t getColorControl() const {
            return color_control;
        }
        virtual uint32_t getColorAccent() const {
            return color_accent;
        }
        virtual uint32_t getColorAccentDark() const {
            return color_accent_dark;
        }

        virtual uint32_t getColorOnError() const {
            return color_onError;
        }
        virtual uint32_t getColorOnBackground() const {
            return color_onBackground;
        }
        virtual uint32_t getColorOnAccent() const {
            return color_onAccent;
        }
    };
}