#pragma once

#include "resource/ResourceManager.h"
#include "ui/Font.h"
#include "ui/Theme.h"
#include "ui/drawable/BitmapImage.h"

namespace Material {
    using namespace Ghurund::UI;

    class Theme:public Ghurund::UI::Theme {
    public:
        Theme(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context) {
            buttonFont = ghnew Ghurund::UI::Font("fonts/lato_medium.ttf", "Lato Medium", 10, FW_MEDIUM, false);
            buttonFont->init(context.Graphics2D);
            listHeaderFont = ghnew Ghurund::UI::Font("fonts/lato_light.ttf", "Lato Light", 14, FW_LIGHT, false);
            listHeaderFont->init(context.Graphics2D);
            primaryTextFont = ghnew Ghurund::UI::Font("fonts/lato_regular.ttf", "Lato", 11, FW_REGULAR, false);
            primaryTextFont->init(context.Graphics2D);
            secondaryTextFont = ghnew Ghurund::UI::Font("fonts/lato_regular.ttf", "Lato", 10, FW_REGULAR, false);
            secondaryTextFont->init(context.Graphics2D);

            checkBoxChecked = BitmapImage::makeFromImage(context, "icons/checkbox checked 18.png");
            checkBoxUnchecked = BitmapImage::makeFromImage(context, "icons/checkbox unchecked 18.png");
            radioButtonChecked = BitmapImage::makeFromImage(context, "icons/radiobutton checked 18.png");
            radioButtonUnchecked = BitmapImage::makeFromImage(context, "icons/radiobutton unchecked 18.png");
            arrowDown = BitmapImage::makeFromImage(context, "icons/arrow down 18.png");
            arrowUp = BitmapImage::makeFromImage(context, "icons/arrow up 18.png");
        }
    };

    class Dark:public Theme {
    public:
        static constexpr uint32_t color_error = 0xffCF6679;
        static constexpr uint32_t color_onBackground = 0xffFFFFFF;
        static constexpr uint32_t color_onError = 0xff000000;
        static constexpr uint32_t color_onAccent = 0xffffffff;
        uint32_t color_accent;
        static constexpr uint32_t color_accent_dark = 0xff005B99;
        static constexpr uint32_t color_background = 0xff121212;
        static constexpr uint32_t color_control = 0xffffffff;

        Dark(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context, uint32_t accent):Theme(resourceManager, context), color_accent(accent) {}

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

    class Light:public Theme {
    public:
        static constexpr uint32_t color_error = 0xffB00020;
        static constexpr uint32_t color_onBackground = 0xff000000;
        static constexpr uint32_t color_onError = 0xffFFFFFF;
        static constexpr uint32_t color_onAccent = 0xffffffff;
        uint32_t color_accent;
        static constexpr uint32_t color_accent_dark = 0xff005B99;
        static constexpr uint32_t color_background = 0xffFFFFFF;
        static constexpr uint32_t color_control = 0xff000000;

        Light(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context, uint32_t accent):Theme(resourceManager, context), color_accent(accent) {}

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