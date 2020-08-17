#pragma once

#include "ui/gdi/GdiFont.h"
#include "ui/widget/TextButton.h"
#include <iostream>

namespace Material {
    static constexpr unsigned int colorWithAlpha(float alpha, unsigned int color) {
        unsigned int a = alpha * 0xff;
        return ((a & 0xff) << 24) | (color & 0xffffff);
    }

    constexpr float emphasis_high = 0.87f;
    constexpr float emphasis_medium = 0.6f;
    constexpr float emphasis_disabled = 0.38f;

    class Theme {
    private:
        Ghurund::UI::Font* buttonFont, * primaryTextFont, * secondaryTextFont;

    public:
        Theme() {
            buttonFont = ghnew Ghurund::UI::Font("Arial", 10, 400, false);
            primaryTextFont = ghnew Ghurund::UI::Font("Arial", 11, 400, false);
            secondaryTextFont = ghnew Ghurund::UI::Font("Arial", 10, 400, false);
        }

        virtual ~Theme() {
            buttonFont->release();
            primaryTextFont->release();
            secondaryTextFont->release();
        }

        Ghurund::UI::Font* getButtonFont() {
            return buttonFont;
        }

        Ghurund::UI::Font* getPrimaryTextFont() {
            return primaryTextFont;
        }

        Ghurund::UI::Font* getSecondaryTextFont() {
            return secondaryTextFont;
        }

        virtual unsigned int getColorBackground() = 0;

        virtual unsigned int getColorOnPrimary() = 0;

        virtual unsigned int getColorOnSurface() = 0;

        virtual unsigned int getColorSurface() = 0;

        unsigned int getTextColorPrimaryOnPrimary() {
            return colorWithAlpha(emphasis_high, getColorOnPrimary());
        }

        unsigned int getTextColorSecondaryOnPrimary() {
            return colorWithAlpha(emphasis_medium, getColorOnPrimary());
        }

        unsigned int getTextColorPrimaryOnSurface() {
            return colorWithAlpha(emphasis_high, getColorOnSurface());
        }

        unsigned int getTextColorSecondaryOnSurface() {
            return colorWithAlpha(emphasis_medium, getColorOnSurface());
        }

        unsigned int getTextColorDisabledOnSurface() {
            return colorWithAlpha(emphasis_disabled, getColorOnSurface());
        }

        std::function<void(Ghurund::UI::Control&)> getTextButtonStateHandler() {
            return [this](Ghurund::UI::Control& control) {
                Ghurund::UI::TextButton& button = (Ghurund::UI::TextButton&)control;
                if (!button.Enabled) {
                    std::cout << "enabled\n";
                    button.TextColor = getTextColorDisabledOnSurface();
                    button.BorderColor = getTextColorDisabledOnSurface();
                    button.repaint();
                } else if (button.Hovered) {
                    std::cout << "hovered\n";
                    button.TextColor = getTextColorSecondaryOnSurface();
                    button.BorderColor = getTextColorSecondaryOnSurface();
                    button.repaint();
                } else if (button.Pressed) {
                    std::cout << "pressed\n";
                    button.TextColor = getTextColorPrimaryOnSurface();
                    button.BorderColor = getTextColorSecondaryOnSurface();
                    button.repaint();
                } else {
                    std::cout << "idle\n";
                    button.TextColor = getTextColorSecondaryOnSurface();
                    button.BorderColor = getTextColorDisabledOnSurface();
                    button.repaint();
                }
            };
        }
    };

    class Dark:public Theme {
    public:
        static constexpr unsigned int color_error = 0xCF6679;
        static constexpr unsigned int color_onBackground = 0xFFFFFF;
        static constexpr unsigned int color_onError = 0x000000;
        static constexpr unsigned int color_onPrimary = 0x000000;
        static constexpr unsigned int color_onSecondary = 0x000000;
        static constexpr unsigned int color_onSurface = 0xFFFFFF;
        static constexpr unsigned int color_primary = 0xBA86FC;
        static constexpr unsigned int color_primary_dark = 0x000000;
        static constexpr unsigned int color_primary_variant = 0x3700B3;
        static constexpr unsigned int color_secondary = 0x03DAC6;
        static constexpr unsigned int color_secondary_variant = 0x03DAC6;
        static constexpr unsigned int color_surface = 0x121212;

        static constexpr unsigned int color_textPrimary_onPrimary = colorWithAlpha(emphasis_high, color_onPrimary);
        static constexpr unsigned int color_textPrimary_onSecondary = colorWithAlpha(emphasis_high, color_onSecondary);
        static constexpr unsigned int color_textPrimary_onSurface = colorWithAlpha(emphasis_high, color_onSurface);

        static constexpr unsigned int color_textSecondary_onPrimary = colorWithAlpha(emphasis_medium, color_onPrimary);
        static constexpr unsigned int color_textSecondary_onSecondary = colorWithAlpha(emphasis_medium, color_onSecondary);
        static constexpr unsigned int color_textSecondary_onSurface = colorWithAlpha(emphasis_medium, color_onSurface);

        static constexpr unsigned int color_textDisabled_onPrimary = colorWithAlpha(emphasis_disabled, color_onPrimary);
        static constexpr unsigned int color_textDisabled_onSecondary = colorWithAlpha(emphasis_disabled, color_onSecondary);
        static constexpr unsigned int color_textDisabled_onSurface = colorWithAlpha(emphasis_disabled, color_onSurface);

        virtual unsigned int getColorBackground() {
            return 0xff121212;
        }

        virtual unsigned int getColorSurface() {
            return 0xff121212;
        }

        virtual unsigned int getColorOnPrimary() {
            return 0xff000000;
        }

        virtual unsigned int getColorOnSurface() {
            return 0xffFFFFFF;
        }
    };

    class Light:public Theme {
    public:
        static constexpr unsigned int color_error = 0xB00020;
        static constexpr unsigned int color_onBackground = 0x000000;
        static constexpr unsigned int color_onError = 0xFFFFFF;
        static constexpr unsigned int color_onPrimary = 0xFFFFFF;
        static constexpr unsigned int color_onSecondary = 0x000000;
        static constexpr unsigned int color_onSurface = 0x000000;
        static constexpr unsigned int color_primary = 0x6200EE;
        static constexpr unsigned int color_primary_dark = 0x3700B3;
        static constexpr unsigned int color_primary_variant = 0x3700B3;
        static constexpr unsigned int color_secondary = 0x03DAC6;
        static constexpr unsigned int color_secondary_variant = 0x018786;
        static constexpr unsigned int color_surface = 0xFFFFFF;

        static constexpr unsigned int color_textPrimary_onPrimary = colorWithAlpha(emphasis_high, color_onPrimary);
        static constexpr unsigned int color_textPrimary_onSecondary = colorWithAlpha(emphasis_high, color_onSecondary);
        static constexpr unsigned int color_textPrimary_onSurface = colorWithAlpha(emphasis_high, color_onSurface);

        static constexpr unsigned int color_textSecondary_onPrimary = colorWithAlpha(emphasis_medium, color_onPrimary);
        static constexpr unsigned int color_textSecondary_onSecondary = colorWithAlpha(emphasis_medium, color_onSecondary);
        static constexpr unsigned int color_textSecondary_onSurface = colorWithAlpha(emphasis_medium, color_onSurface);

        static constexpr unsigned int color_textDisabled_onPrimary = colorWithAlpha(emphasis_disabled, color_onPrimary);
        static constexpr unsigned int color_textDisabled_onSecondary = colorWithAlpha(emphasis_disabled, color_onSecondary);
        static constexpr unsigned int color_textDisabled_onSurface = colorWithAlpha(emphasis_disabled, color_onSurface);

        virtual unsigned int getColorBackground() {
            return 0xffFFFFFF;
        }

        virtual unsigned int getColorSurface() {
            return 0xffFFFFFF;
        }

        virtual unsigned int getColorOnPrimary() {
            return 0xffFFFFFF;
        }

        virtual unsigned int getColorOnSurface() {
            return 0xff000000;
        }
    };
}