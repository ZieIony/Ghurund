#pragma once

#include "core/SharedPointer.h"

#include "ui/style/Style.h"
#include "ui/control/Border.h"
#include "ui/control/Shadow.h"
#include "ui/control/Control.h"
#include "ui/control/TextBlockStyle.h"
#include "ui/control/ImageView.h"
#include "ui/drawable/BitmapImage.h"
#include "ui/widget/ClickResponseView.h"
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
        //static const inline float state_activated = 0.4f;
        //static const inline float state_disabled = 0.08f;

        SeparatorHorizontalStyle separatorHorizontalStyle;
        SeparatorVerticalStyle separatorVerticalStyle;
        ProgressBarStyle progressBarStyle;

        TextBlockButtonStyle textViewButtonStyle;
        TextBlockPrimaryStyle textViewPrimaryStyle;
        TextBlockSecondaryStyle textViewSecondaryStyle;
        TextBlockHeaderStyle textViewHeaderStyle;
        TextBlockButtonOnAccentStyle textViewButtonOnAccentStyle;
        TextBlockPrimaryOnAccentStyle textViewPrimaryOnAccentStyle;
        TextBlockSecondaryOnAccentStyle textViewSecondaryOnAccentStyle;
        TextBlockHeaderOnAccentStyle textViewHeaderOnAccentStyle;

        ColorViewControlStyle colorViewControlStyle;
        ColorViewAccentStyle colorViewAccentStyle;
        ColorViewBackgroundStyle colorViewBackgroundStyle;

        ImageViewStyle imageViewStyle;
        ImageViewOnBackgroundStyle imageViewOnBackgroundStyle;
        ImageViewOnAccentStyle imageViewOnAccentStyle;
        ImageViewAccentStyle imageViewAccentStyle;

        BorderOnBackgroundStyle borderOnBackgroundStyle;
        BorderAccentStyle borderAccentStyle;
        ShadowButtonStyle shadowButtonStyle;
        ClickResponseViewOnBackgroundStyle clickResponseViewOnBackgroundStyle;
        ClickResponseViewOnAccentStyle clickResponseViewOnAccentStyle;

        Map<StyleKey, Style*> styles;
        PointerMap<TextFormatKey, TextFormat*> textFormats;
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
        static inline const StyleKey STYLE_TEXTBLOCK_BUTTON = WString(L"textBlock_button");
        static inline const StyleKey STYLE_TEXTBLOCK_PRIMARY = WString(L"textBlock_primary");
        static inline const StyleKey STYLE_TEXTBLOCK_SECONDARY = WString(L"textBlock_secondary");
        static inline const StyleKey STYLE_TEXTBLOCK_HEADER = WString(L"textBlock_header");
        static inline const StyleKey STYLE_TEXTBLOCK_BUTTON_ONACCENT = WString(L"textBlock_button_onAccent");
        static inline const StyleKey STYLE_TEXTBLOCK_PRIMARY_ONACCENT = WString(L"textBlock_primary_onAccent");
        static inline const StyleKey STYLE_TEXTBLOCK_SECONDARY_ONACCENT = WString(L"textBlock_secondary_onAccent");
        static inline const StyleKey STYLE_TEXTBLOCK_HEADER_ONACCENT = WString(L"textBlock_header_onAccent");
        static inline const StyleKey STYLE_COLORVIEW_BACKGROUND = WString(L"colorView_background");
        static inline const StyleKey STYLE_COLORVIEW_CONTROL = WString(L"colorView_control");
        static inline const StyleKey STYLE_COLORVIEW_ACCENT = WString(L"colorView_accent");
        static inline const StyleKey STYLE_IMAGEVIEW = WString(L"imageView");
        static inline const StyleKey STYLE_IMAGEVIEW_ONBACKGROUND = WString(L"imageView_onBackground");
        static inline const StyleKey STYLE_IMAGEVIEW_ONACCENT = WString(L"imageView_onAccent");
        static inline const StyleKey STYLE_IMAGEVIEW_ACCENT = WString(L"imageView_accent");
        static inline const StyleKey STYLE_BORDER_ONBACKGROUND = WString(L"border_onBackground");
        static inline const StyleKey STYLE_BORDER_ACCENT = WString(L"border_accent");
        static inline const StyleKey STYLE_SHADOW_BUTTON = WString(L"shadow_button");
        static inline const StyleKey STYLE_CLICKRESPONSEVIEW_ONBACKGROUND = WString(L"clickResponseView_onBackground");
        static inline const StyleKey STYLE_CLICKRESPONSEVIEW_ONACCENT = WString(L"clickResponseView_onAccent");

        static inline const TextFormatKey TEXTFORMAT_BUTTON = WString(L"button");
        static inline const TextFormatKey TEXTFORMAT_LIST_HEADER = WString(L"listHeader");
        static inline const TextFormatKey TEXTFORMAT_TEXT_PRIMARY = WString(L"textPrimary");
        static inline const TextFormatKey TEXTFORMAT_TEXT_SECONDARY = WString(L"textSecondary");

        // base
        static inline const ColorKey COLOR_BACKGR0UND = WString(L"background");
        static inline const ColorKey COLOR_FOREGROUND_ONBACKGROUND = WString(L"foreground_onBackground");
        static inline const ColorKey COLOR_FOREGROUND_ONACCENT = WString(L"foreground_onAccent");
        static inline const ColorKey COLOR_ACCENT = WString(L"accent");

        // generated
        static inline const ColorKey COLOR_CONTROL = WString(L"control");
        static inline const ColorKey COLOR_PRIMARY_ONBACKGROUND = WString(L"primary_onBackground");
        static inline const ColorKey COLOR_SECONDARY_ONBACKGROUND = WString(L"secondary_onBackground");
        static inline const ColorKey COLOR_DISABLED_ONBACKGROUND = WString(L"disabled_onBackground");
        static inline const ColorKey COLOR_HIGHLIGHT_ONBACKGROUND = WString(L"highlight_onBackground");
        static inline const ColorKey COLOR_PRIMARY_ONACCENT = WString(L"primary_onAccent");
        static inline const ColorKey COLOR_SECONDARY_ONACCENT = WString(L"secondary_onAccent");
        static inline const ColorKey COLOR_DISABLED_ONACCENT = WString(L"disabled_onAccent");
        static inline const ColorKey COLOR_HIGHLIGHT_ONACCENT = WString(L"highlight_onAccent");

        Theme();

        void updateColors();

        inline Map<StyleKey, Style*>& getStyles() {
            return styles;
        }

        __declspec(property(get = getStyles)) Map<StyleKey, Style*>& Styles;

        inline PointerMap<TextFormatKey, TextFormat*>& getTextStyles() {
            return textFormats;
        }

        __declspec(property(get = getTextStyles)) PointerMap<TextFormatKey, TextFormat*>& TextFormats;

        inline Map<ColorKey, Color>& getColors() {
            return colors;
        }

        __declspec(property(get = getColors)) Map<ColorKey, Color>& Colors;

        inline PointerMap<ImageKey, BitmapImage*>& getImages() {
            return images;
        }

        __declspec(property(get = getImages)) PointerMap<ImageKey, BitmapImage*>& Images;
    };
}