#pragma once

#include "ui/Theme.h"
#include "ui/gdi/GdiFont.h"
#include "ui/gdi/GdiImage.h"

namespace Material {
    class Theme:public Ghurund::UI::Theme {
    public:
        Theme() {
            buttonFont = ghnew Ghurund::UI::Font("fonts/lato_medium.ttf", "Lato Medium", 10, FW_MEDIUM, false);
            listHeaderFont = ghnew Ghurund::UI::Font("fonts/lato_light.ttf", "Lato Light", 14, FW_LIGHT, false);
            primaryTextFont = ghnew Ghurund::UI::Font("fonts/lato_regular.ttf", "Lato", 11, FW_REGULAR, false);
            secondaryTextFont = ghnew Ghurund::UI::Font("fonts/lato_regular.ttf", "Lato", 10, FW_REGULAR, false);

            checkBoxChecked = ghnew Ghurund::UI::GdiImage(L"icons/checkbox checked 18.png");
            checkBoxUnchecked = ghnew Ghurund::UI::GdiImage(L"icons/checkbox unchecked 18.png");
            radioButtonChecked = ghnew Ghurund::UI::GdiImage(L"icons/radiobutton checked 18.png");
            radioButtonUnchecked = ghnew Ghurund::UI::GdiImage(L"icons/radiobutton unchecked 18.png");
        }
    };

    class Dark:public Theme {
    public:
        static constexpr unsigned int color_error = 0xffCF6679;
        static constexpr unsigned int color_onBackground = 0xffFFFFFF;
        static constexpr unsigned int color_onError = 0xff000000;
        static constexpr unsigned int color_onAccent = 0xffffffff;
        unsigned int color_accent;
        static constexpr unsigned int color_accent_dark = 0xff005B99;
        static constexpr unsigned int color_background = 0xff121212;
        static constexpr unsigned int color_control = 0xffffffff;

        Dark(unsigned int accent):color_accent(accent) {}

        virtual unsigned int getColorError() const {
            return color_error;
        }
        virtual unsigned int getColorBackground() const {
            return color_background;
        }
        virtual unsigned int getColorControl() const {
            return color_control;
        }
        virtual unsigned int getColorAccent() const {
            return color_accent;
        }
        virtual unsigned int getColorAccentDark() const {
            return color_accent_dark;
        }

        virtual unsigned int getColorOnError() const {
            return color_onError;
        }
        virtual unsigned int getColorOnBackground() const {
            return color_onBackground;
        }
        virtual unsigned int getColorOnAccent() const {
            return color_onAccent;
        }
    };

    class Light:public Theme {
    public:
        static constexpr unsigned int color_error = 0xffB00020;
        static constexpr unsigned int color_onBackground = 0xff000000;
        static constexpr unsigned int color_onError = 0xffFFFFFF;
        static constexpr unsigned int color_onAccent = 0xffffffff;
        unsigned int color_accent;
        static constexpr unsigned int color_accent_dark = 0xff005B99;
        static constexpr unsigned int color_background = 0xffFFFFFF;
        static constexpr unsigned int color_control = 0xff000000;

        Light(unsigned int accent):color_accent(accent) {}

        virtual unsigned int getColorError() const {
            return color_error;
        }
        virtual unsigned int getColorBackground() const {
            return color_background;
        }
        virtual unsigned int getColorControl() const {
            return color_control;
        }
        virtual unsigned int getColorAccent() const {
            return color_accent;
        }
        virtual unsigned int getColorAccentDark() const {
            return color_accent_dark;
        }

        virtual unsigned int getColorOnError() const {
            return color_onError;
        }
        virtual unsigned int getColorOnBackground() const {
            return color_onBackground;
        }
        virtual unsigned int getColorOnAccent() const {
            return color_onAccent;
        }
    };
}