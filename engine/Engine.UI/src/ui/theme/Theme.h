#pragma once

#include "AttributeKey.h"
#include "core/SharedPointer.h"
#include "core/collection/Map.h"

#include "ui/Color.h"
#include "ui/drawable/Drawable.h"
#include "ui/text/TextFormat.h"
#include "DrawableProvider.h"
#include "LayoutProvider.h"

namespace Ghurund::UI {

    typedef AttributeKey<Color> ColorKey;
    typedef AttributeKey<Drawable> DrawableKey;
    typedef AttributeKey<TextFormat> TextFormatKey;
    typedef AttributeKey<Control> LayoutKey;

    class Theme {
    private:
        struct ColorMapTraits {
            using key_t = ColorKey;
            using value_t = Color;
            using data_t = KeyValuePair<key_t, value_t>;

            Color defaultValue = Color(0);

            inline const key_t& getKey(const data_t& data) const {
                return data.key;
            }

            inline data_t makeData(const key_t& key) const {
                return { key, defaultValue };
            }

            inline data_t makeData(const key_t& key, const value_t& value) const {
                return { key, value };
            }
        };

        static const inline float emphasis_high = 0.87f;
        static const inline float emphasis_medium = 0.6f;
        static const inline float emphasis_disabled = 0.38f;

        static const inline float highlight = 0.25f;

        static const inline float state_normal = 0.12f;
        //static const inline float state_activated = 0.4f;
        //static const inline float state_disabled = 0.08f;

        Ghurund::Core::Map<TextFormatKey, Ghurund::Core::SharedPointer<TextFormat>> textFormats;
        Ghurund::Core::Map<ColorKey, Color, SimpleAllocator, ColorMapTraits> colors;
        Ghurund::Core::Map<DrawableKey, std::shared_ptr<DrawableProvider>> drawables;
        Ghurund::Core::Map<LayoutKey, std::shared_ptr<LayoutProvider>> layouts;

    public:
        static inline const DrawableKey DRAWABLE_CHECKBOX_CHECKED = DrawableKey("checkBox_checked");
        static inline const DrawableKey DRAWABLE_CHECKBOX_UNCHECKED = DrawableKey("checkBox_unchecked");
        static inline const DrawableKey DRAWABLE_RADIOBUTTON_CHECKED = DrawableKey("radioButton_checked");
        static inline const DrawableKey DRAWABLE_RADIOBUTTON_UNCHECKED = DrawableKey("radioButton_unchecked");
        static inline const DrawableKey DRAWABLE_ARROWUP = DrawableKey("arrowUp");
        static inline const DrawableKey DRAWABLE_ARROWDOWN = DrawableKey("arrowDown");
        static inline const DrawableKey DRAWABLE_ARROWRIGHT = DrawableKey("arrowRight");

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

        inline Map<TextFormatKey, SharedPointer<TextFormat>>& getTextFormats() {
            return textFormats;
        }

        inline const Map<TextFormatKey, SharedPointer<TextFormat>>& getTextFormats() const {
            return textFormats;
        }

        __declspec(property(get = getTextFormats)) Map<TextFormatKey, SharedPointer<TextFormat>>& TextFormats;

        inline Ghurund::Core::Map<ColorKey, Color, SimpleAllocator, ColorMapTraits>& getColors() {
            return colors;
        }

        inline const Ghurund::Core::Map<ColorKey, Color, SimpleAllocator, ColorMapTraits>& getColors() const {
            return colors;
        }

        __declspec(property(get = getColors)) Ghurund::Core::Map<ColorKey, Color, SimpleAllocator, ColorMapTraits>& Colors;

        inline Map<DrawableKey, std::shared_ptr<DrawableProvider>>& getDrawables() {
            return drawables;
        }

        inline const Map<DrawableKey, std::shared_ptr<DrawableProvider>>& getDrawables() const {
            return drawables;
        }

        __declspec(property(get = getDrawables)) Map<DrawableKey, std::shared_ptr<DrawableProvider>>& Drawables;

        inline Ghurund::Core::Map<LayoutKey, std::shared_ptr<LayoutProvider>>& getLayouts() {
            return layouts;
        }

        inline const Ghurund::Core::Map<LayoutKey, std::shared_ptr<LayoutProvider>>& getLayouts() const {
            return layouts;
        }

        __declspec(property(get = getLayouts)) Ghurund::Core::Map<LayoutKey, std::shared_ptr<LayoutProvider>>& Layouts;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Theme>();
}