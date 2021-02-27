#pragma once

#include "core/SharedPointer.h"

#include "ui/Color.h"
#include "ui/drawable/BitmapImage.h"
#include "ui/font/TextFormat.h"
#include "ui/style/Style.h"

namespace Ghurund::UI {
    struct ColorKey {
        const AString str;
        ColorKey(const AString& str):str(str) {}
        bool operator==(const ColorKey& other) const {
            return str == other.str;
        }
    };

    struct StyleKey {
        const AString str;
        StyleKey(const AString& str):str(str) {}
        bool operator==(const StyleKey& other) const {
            return str == other.str;
        }
    };

    struct ImageKey {
        const AString str;
        ImageKey(const AString& str):str(str) {}
        bool operator==(const ImageKey& other) const {
            return str == other.str;
        }
    };

    struct TextFormatKey {
        const AString str;
        TextFormatKey(const AString& str):str(str) {}
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

        Map<StyleKey, Style*> styles;
        PointerMap<TextFormatKey, TextFormat*> textFormats;
        Map<ColorKey, Color> colors;
        PointerMap<ImageKey, BitmapImage*> images;
        
        // xml reader doesn't support wchar_t
        Map<const Type*, AString> layouts;

    public:
        static inline const ImageKey IMAGE_CHECKBOX_CHECKED = AString("checkBox_checked");
        static inline const ImageKey IMAGE_CHECKBOX_UNCHECKED = AString("checkBox_unchecked");
        static inline const ImageKey IMAGE_RADIOBUTTON_CHECKED = AString("radioButton_checked");
        static inline const ImageKey IMAGE_RADIOBUTTON_UNCHECKED = AString("radioButton_unchecked");
        static inline const ImageKey IMAGE_ARROWUP = AString("arrowUp");
        static inline const ImageKey IMAGE_ARROWDOWN = AString("arrowDown");

        static inline const StyleKey STYLE_CHECKBOX = StyleKey("CheckBox");
        static inline const StyleKey STYLE_RADIOBUTTON = StyleKey("RadioButton");
        static inline const StyleKey STYLE_SEPARATOR_HORIZONTAL = StyleKey("Separator_horizontal");
        static inline const StyleKey STYLE_SEPARATOR_VERTICAL = StyleKey("Separator_vertical");
        static inline const StyleKey STYLE_PROGRESSBAR = StyleKey("ProgressBar");
        static inline const StyleKey STYLE_TEXTBLOCK = StyleKey("TextBlock");
        static inline const StyleKey STYLE_TEXTBLOCK_BUTTON = StyleKey("TextBlock_button");
        static inline const StyleKey STYLE_TEXTBLOCK_PRIMARY = StyleKey("TextBlock_primary");
        static inline const StyleKey STYLE_TEXTBLOCK_SECONDARY = StyleKey("TextBlock_secondary");
        static inline const StyleKey STYLE_TEXTBLOCK_HEADER = StyleKey("TextBlock_header");
        static inline const StyleKey STYLE_TEXTBLOCK_BUTTON_ONACCENT = StyleKey("TextBlock_button_onAccent");
        static inline const StyleKey STYLE_TEXTBLOCK_PRIMARY_ONACCENT = StyleKey("TextBlock_primary_onAccent");
        static inline const StyleKey STYLE_TEXTBLOCK_SECONDARY_ONACCENT = StyleKey("TextBlock_secondary_onAccent");
        static inline const StyleKey STYLE_TEXTBLOCK_HEADER_ONACCENT = StyleKey("TextBlock_header_onAccent");
        static inline const StyleKey STYLE_COLORVIEW_BACKGROUND = StyleKey("ColorView_background");
        static inline const StyleKey STYLE_COLORVIEW_CONTROL = StyleKey("ColorView_control");
        static inline const StyleKey STYLE_COLORVIEW_ACCENT = StyleKey("ColorView_accent");
        static inline const StyleKey STYLE_IMAGEVIEW = StyleKey("ImageView");
        static inline const StyleKey STYLE_IMAGEVIEW_ONBACKGROUND = StyleKey("ImageView_onBackground");
        static inline const StyleKey STYLE_IMAGEVIEW_ONACCENT = StyleKey("ImageView_onAccent");
        static inline const StyleKey STYLE_IMAGEVIEW_ACCENT = StyleKey("ImageView_accent");
        static inline const StyleKey STYLE_BORDER_ONBACKGROUND = StyleKey("Border_onBackground");
        static inline const StyleKey STYLE_BORDER_ACCENT = StyleKey("Border_accent");
        static inline const StyleKey STYLE_SHADOW_BUTTON = StyleKey("Shadow_button");
        static inline const StyleKey STYLE_CLICKRESPONSEVIEW_ONBACKGROUND = StyleKey("ClickResponseView_onBackground");
        static inline const StyleKey STYLE_CLICKRESPONSEVIEW_ONACCENT = StyleKey("ClickResponseView_onAccent");
        static inline const StyleKey STYLE_STATEINDICATOR_ONBACKGROUND = StyleKey("StateIndicator_onBackground");
        static inline const StyleKey STYLE_STATEINDICATOR_ONACCENT = StyleKey("StateIndicator_onAccent");

        static inline const TextFormatKey TEXTFORMAT_BUTTON = TextFormatKey("button");
        static inline const TextFormatKey TEXTFORMAT_LIST_HEADER = TextFormatKey("listHeader");
        static inline const TextFormatKey TEXTFORMAT_TEXT_PRIMARY = TextFormatKey("textPrimary");
        static inline const TextFormatKey TEXTFORMAT_TEXT_SECONDARY = TextFormatKey("textSecondary");

        // base
        static inline const ColorKey COLOR_BACKGR0UND = ColorKey("background");
        static inline const ColorKey COLOR_FOREGROUND_ONBACKGROUND = ColorKey("foreground_onBackground");
        static inline const ColorKey COLOR_FOREGROUND_ONACCENT = ColorKey("foreground_onAccent");
        static inline const ColorKey COLOR_ACCENT = ColorKey("accent");

        // generated
        static inline const ColorKey COLOR_CONTROL = ColorKey("control");
        static inline const ColorKey COLOR_PRIMARY_ONBACKGROUND = ColorKey("primary_onBackground");
        static inline const ColorKey COLOR_SECONDARY_ONBACKGROUND = ColorKey("secondary_onBackground");
        static inline const ColorKey COLOR_DISABLED_ONBACKGROUND = ColorKey("disabled_onBackground");
        static inline const ColorKey COLOR_HIGHLIGHT_ONBACKGROUND = ColorKey("highlight_onBackground");
        static inline const ColorKey COLOR_PRIMARY_ONACCENT = ColorKey("primary_onAccent");
        static inline const ColorKey COLOR_SECONDARY_ONACCENT = ColorKey("secondary_onAccent");
        static inline const ColorKey COLOR_DISABLED_ONACCENT = ColorKey("disabled_onAccent");
        static inline const ColorKey COLOR_HIGHLIGHT_ONACCENT = ColorKey("highlight_onAccent");

        virtual ~Theme() {}

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

        inline Map<const Type*, AString>& getLayouts() {
            return layouts;
        }

        __declspec(property(get = getLayouts)) Map<const Type*, AString>& Layouts;
    };
}