#pragma once

#include "core/SharedPointer.h"
#include "core/collection/Map.h"

#include "ui/Color.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/text/TextFormat.h"
#include "ui/style/Style.h"

namespace Ghurund::UI {
    template<typename Type>
    class AttributeKey {
    private:
        Ghurund::Core::AString str;

    public:
        AttributeKey(const Ghurund::Core::AString& str) :str(str) {}

        const Ghurund::Core::AString& getValue() const {
            return str;
        }

        __declspec(property(get = getValue)) const Ghurund::Core::AString& Value;

        bool operator==(const AttributeKey& other) const {
            return str == other.str;
        }
    };

    typedef AttributeKey<Color> ColorKey;
    typedef AttributeKey<Style> StyleKey;
    typedef AttributeKey<ImageDrawable> DrawableKey;
    typedef AttributeKey<TextFormat> TextFormatKey;

    class Theme {
    private:
        static const inline float emphasis_high = 0.87f;
        static const inline float emphasis_medium = 0.6f;
        static const inline float emphasis_disabled = 0.38f;

        static const inline float highlight = 0.25f;

        static const inline float state_normal = 0.12f;
        //static const inline float state_activated = 0.4f;
        //static const inline float state_disabled = 0.08f;

        Ghurund::Core::Map<StyleKey, Style*> styles;
        Map<TextFormatKey, SharedPointer<TextFormat>> textFormats;
        Ghurund::Core::Map<ColorKey, Color> colors;
        Map<DrawableKey, SharedPointer<Drawable>> drawables;
        
        // xml reader doesn't support wchar_t
        Ghurund::Core::Map<const Ghurund::Core::Type*, Ghurund::Core::AString> layouts;

    public:
        static inline const DrawableKey DRAWABLE_CHECKBOX_CHECKED = DrawableKey("checkBox_checked");
        static inline const DrawableKey DRAWABLE_CHECKBOX_UNCHECKED = DrawableKey("checkBox_unchecked");
        static inline const DrawableKey DRAWABLE_RADIOBUTTON_CHECKED = DrawableKey("radioButton_checked");
        static inline const DrawableKey DRAWABLE_RADIOBUTTON_UNCHECKED = DrawableKey("radioButton_unchecked");
        static inline const DrawableKey DRAWABLE_ARROWUP = DrawableKey("arrowUp");
        static inline const DrawableKey DRAWABLE_ARROWDOWN = DrawableKey("arrowDown");
        static inline const DrawableKey DRAWABLE_ARROWRIGHT = DrawableKey("arrowRight");

        static inline const StyleKey STYLE_CHECKBOX = StyleKey("CheckBox");
        static inline const StyleKey STYLE_CHECKBOX_EXPANDABLE = StyleKey("CheckBox_expandable");
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
        static inline const StyleKey STYLE_DRAWABLEVIEW = StyleKey("DrawableView");
        static inline const StyleKey STYLE_DRAWABLEVIEW_ONBACKGROUND = StyleKey("DrawableView_onBackground");
        static inline const StyleKey STYLE_DRAWABLEVIEW_ONACCENT = StyleKey("DrawableView_onAccent");
        static inline const StyleKey STYLE_DRAWABLEVIEW_ACCENT = StyleKey("DrawableView_accent");
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

        Theme();

        virtual ~Theme() {}

        void updateColors();

        inline Ghurund::Core::Map<StyleKey, Style*>& getStyles() {
            return styles;
        }

        inline const Ghurund::Core::Map<StyleKey, Style*>& getStyles() const {
            return styles;
        }

        __declspec(property(get = getStyles)) Ghurund::Core::Map<StyleKey, Style*>& Styles;

        inline Map<TextFormatKey, SharedPointer<TextFormat>>& getTextFormats() {
            return textFormats;
        }

        inline const Map<TextFormatKey, SharedPointer<TextFormat>>& getTextFormats() const {
            return textFormats;
        }

        __declspec(property(get = getTextFormats)) Map<TextFormatKey, SharedPointer<TextFormat>>& TextFormats;

        inline Ghurund::Core::Map<ColorKey, Color>& getColors() {
            return colors;
        }

        inline const Ghurund::Core::Map<ColorKey, Color>& getColors() const {
            return colors;
        }

        __declspec(property(get = getColors)) Ghurund::Core::Map<ColorKey, Color>& Colors;

        inline Map<DrawableKey, SharedPointer<Drawable>>& getDrawables() {
            return drawables;
        }

        inline const Map<DrawableKey, SharedPointer<Drawable>>& getDrawables() const {
            return drawables;
        }

        __declspec(property(get = getDrawables)) Map<DrawableKey, SharedPointer<Drawable>>& Drawables;

        inline Ghurund::Core::Map<const Ghurund::Core::Type*, Ghurund::Core::AString>& getLayouts() {
            return layouts;
        }

        inline const Ghurund::Core::Map<const Ghurund::Core::Type*, Ghurund::Core::AString>& getLayouts() const {
            return layouts;
        }

        __declspec(property(get = getLayouts)) Ghurund::Core::Map<const Ghurund::Core::Type*, Ghurund::Core::AString>& Layouts;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Theme>();
}