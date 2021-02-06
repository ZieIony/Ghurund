#pragma once

#include "core/SharedPointer.h"

#include "ui/style/Style.h"
#include "ui/control/Control.h"
#include "ui/control/TextBlockStyle.h"
#include "ui/drawable/BitmapImage.h"
#include "ui/widget/SeparatorStyle.h"
#include "ui/widget/ProgressBar.h"

namespace Ghurund::UI {
    struct ColorKey {
        const WString str;
        ColorKey(const WString& str):str(str) {}
        bool operator==(const ColorKey& other) const {
            return str == other.str;
        }
    };

    struct StyleKey {
        const WString str;
        StyleKey(const WString& str):str(str) {}
        bool operator==(const StyleKey& other) const {
            return str == other.str;
        }
    };

    struct ImageKey {
        const WString str;
        ImageKey(const WString& str):str(str) {}
        bool operator==(const ImageKey& other) const {
            return str == other.str;
        }
    };

    struct TextFormatKey {
        const WString str;
        TextFormatKey(const WString& str):str(str) {}
        bool operator==(const TextFormatKey& other) const {
            return str == other.str;
        }
    };

    class Theme {
    private:
        static const inline float emphasis_high = 0.87f;
        static const inline float emphasis_medium = 0.6f;
        static const inline float emphasis_disabled = 0.38f;

        static const inline float highlight = 0.25f;

        static const inline float state_normal = 0.12f;
        static const inline float state_activated = 0.4f;
        static const inline float state_disabled = 0.08f;

        constexpr uint32_t colorWithAlpha(float alpha, uint32_t color) const {
            uint32_t a = (uint32_t)(alpha * 0xff);
            return ((a & 0xff) << 24) | (color & 0xffffff);
        }

        Style* separatorHorizontalStyle = ghnew SeparatorHorizontalStyle();
        Style* separatorVerticalStyle = ghnew SeparatorVerticalStyle();
        Style* progressBarStyle = ghnew ProgressBarStyle();

        Style* textViewPrimaryStyle = ghnew TextBlockPrimaryStyle();
        Style* textViewSecondaryStyle = ghnew TextBlockSecondaryStyle();
        Style* textViewHeaderStyle = ghnew TextBlockHeaderStyle();

        Map<StyleKey, Style*> styles;
        PointerMap<TextFormatKey, TextStyle*> textStyles;
        Map<ColorKey, Color> colors;
        PointerMap<ImageKey, BitmapImage*> images;

    public:
        static inline const ImageKey IMAGE_CHECKBOX_CHECKED = WString(L"checkBox_checked");
        static inline const ImageKey IMAGE_CHECKBOX_UNCHECKED = WString(L"checkBox_unchecked");
        static inline const ImageKey IMAGE_RADIOBUTTON_CHECKED = WString(L"radioButton_checked");
        static inline const ImageKey IMAGE_RADIOBUTTON_UNCHECKED = WString(L"radioButton_unchecked");
        static inline const ImageKey IMAGE_ARROWUP = WString(L"arrowUp");
        static inline const ImageKey IMAGE_ARROWDOWN = WString(L"arrowDown");

        static inline const StyleKey STYLE_SEPARATOR_HORIZONTAL = WString(L"separator_horizontal");
        static inline const StyleKey STYLE_SEPARATOR_VERTICAL = WString(L"separator_vertical");
        static inline const StyleKey STYLE_PROGRESSBAR = WString(L"progressBar");
        static inline const StyleKey STYLE_TEXTBLOCK_PRIMARY = WString(L"textBlock_primary");
        static inline const StyleKey STYLE_TEXTBLOCK_SECONDARY = WString(L"textBlock_secondary");
        static inline const StyleKey STYLE_TEXTBLOCK_HEADER = WString(L"textBlock_header");

        static inline const TextFormatKey TEXTSTYLE_BUTTON = WString(L"button");
        static inline const TextFormatKey TEXTSTYLE_LIST_HEADER = WString(L"listHeader");
        static inline const TextFormatKey TEXTSTYLE_TEXT_PRIMARY = WString(L"textPrimary");
        static inline const TextFormatKey TEXTSTYLE_TEXT_SECONDARY = WString(L"textSecondary");

        static inline const ColorKey COLOR_ERROR = WString(L"error");
        static inline const ColorKey COLOR_BACKGR0UND = WString(L"background");
        static inline const ColorKey COLOR_CONTROL = WString(L"control");
        static inline const ColorKey COLOR_ACCENT = WString(L"accent");
        static inline const ColorKey COLOR_ON_ERROR = WString(L"onError");
        static inline const ColorKey COLOR_ON_BACKGR0UND = WString(L"onBackground");
        static inline const ColorKey COLOR_ON_ACCENT = WString(L"onAccent");

        Theme() {
            separatorHorizontalStyle = ghnew SeparatorHorizontalStyle();
            separatorVerticalStyle = ghnew SeparatorVerticalStyle();
            progressBarStyle = ghnew ProgressBarStyle();

            textViewPrimaryStyle = ghnew TextBlockPrimaryStyle();
            textViewSecondaryStyle = ghnew TextBlockSecondaryStyle();
            textViewHeaderStyle = ghnew TextBlockHeaderStyle();

            styles.set(STYLE_SEPARATOR_HORIZONTAL, separatorHorizontalStyle);
            styles.set(STYLE_SEPARATOR_VERTICAL, separatorVerticalStyle);
            styles.set(STYLE_PROGRESSBAR, progressBarStyle);
            styles.set(STYLE_TEXTBLOCK_PRIMARY, textViewPrimaryStyle);
            styles.set(STYLE_TEXTBLOCK_SECONDARY, textViewSecondaryStyle);
            styles.set(STYLE_TEXTBLOCK_HEADER, textViewHeaderStyle);
        }

        virtual ~Theme() {
            delete separatorHorizontalStyle;
            delete separatorVerticalStyle;
            delete progressBarStyle;

            delete textViewPrimaryStyle;
            delete textViewSecondaryStyle;
            delete textViewHeaderStyle;
        }

        inline Map<StyleKey, Style*>& getStyles() {
            return styles;
        }

        __declspec(property(get = getStyles)) Map<StyleKey, Style*>& Styles;

        inline PointerMap<TextFormatKey, TextStyle*>& getTextStyles() {
            return textStyles;
        }

        __declspec(property(get = getTextStyles)) PointerMap<TextFormatKey, TextStyle*>& TextStyles;

        inline Map<ColorKey, Color>& getColors() {
            return colors;
        }

        __declspec(property(get = getColors)) Map<ColorKey, Color>& Colors;

        inline PointerMap<ImageKey, BitmapImage*>& getImages() {
            return images;
        }

        __declspec(property(get = getImages)) PointerMap<ImageKey, BitmapImage*>& Images;

        uint32_t getColorControlNormal() {
            return colorWithAlpha(state_normal, Colors[COLOR_CONTROL]);
        }

        __declspec(property(get = getColorControlNormal)) uint32_t ColorControlNormal;

        uint32_t getColorControlDisabled() {
            return colorWithAlpha(state_disabled, Colors[COLOR_CONTROL]);
        }

        __declspec(property(get = getColorControlDisabled)) uint32_t ColorControlDisabled;

        uint32_t getColorControlActivated() {
            return colorWithAlpha(state_activated, Colors[COLOR_CONTROL]);
        }

        __declspec(property(get = getColorControlActivated)) uint32_t ColorControlActivated;

        uint32_t getColorForegroundPrimaryOnError() {
            return colorWithAlpha(emphasis_high, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorForegroundPrimaryOnError)) uint32_t ColorForegroundPrimaryOnError;

        uint32_t getColorForegroundPrimaryOnBackground() {
            return colorWithAlpha(emphasis_high, Colors[COLOR_ON_BACKGR0UND]);
        }

        __declspec(property(get = getColorForegroundPrimaryOnBackground)) uint32_t ColorForegroundPrimaryOnBackground;

        uint32_t getColorForegroundPrimaryOnAccent() {
            return colorWithAlpha(emphasis_high, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorForegroundPrimaryOnAccent)) uint32_t ColorForegroundPrimaryOnAccent;

        uint32_t getColorForegroundSecondaryOnError() {
            return colorWithAlpha(emphasis_medium, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorForegroundSecondaryOnError)) uint32_t ColorForegroundSecondaryOnError;

        uint32_t getColorForegroundSecondaryOnBackground() {
            return colorWithAlpha(emphasis_medium, Colors[COLOR_ON_BACKGR0UND]);
        }

        __declspec(property(get = getColorForegroundSecondaryOnBackground)) uint32_t ColorForegroundSecondaryOnBackground;

        uint32_t getColorForegroundSecondaryOnAccent() {
            return colorWithAlpha(emphasis_medium, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorForegroundSecondaryOnAccent)) uint32_t ColorForegroundSecondaryOnAccent;

        uint32_t getColorForegroundDisabledOnError() {
            return colorWithAlpha(emphasis_disabled, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorForegroundDisabledOnError)) uint32_t ColorForegroundDisabledOnError;

        uint32_t getColorForegroundDisabledOnBackground() {
            return colorWithAlpha(emphasis_disabled, Colors[COLOR_ON_BACKGR0UND]);
        }

        __declspec(property(get = getColorForegroundDisabledOnBackground)) uint32_t ColorForegroundDisabledOnBackground;

        uint32_t getColorForegroundDisabledOnAccent() {
            return colorWithAlpha(emphasis_disabled, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorForegroundDisabledOnAccent)) uint32_t ColorForegroundDisabledOnAccent;

        // highlights

        uint32_t getColorHighlightOnError() {
            return colorWithAlpha(highlight, Colors[COLOR_ON_ERROR]);
        }

        __declspec(property(get = getColorHighlightOnError)) uint32_t ColorHighlightOnError;

        uint32_t getColorHighlightOnBackground() {
            return colorWithAlpha(highlight, Colors[COLOR_ACCENT]);
        }

        __declspec(property(get = getColorHighlightOnBackground)) uint32_t ColorHighlightOnBackground;

        uint32_t getColorHighlightOnAccent() {
            return colorWithAlpha(highlight, Colors[COLOR_ON_ACCENT]);
        }

        __declspec(property(get = getColorHighlightOnAccent)) uint32_t ColorHighlightOnAccent;

    };
}