#pragma once

#include "AttributeKey.h"
#include "LayoutProvider.h"
#include "MaterialProvider.h"
#include "TextureProvider.h"

#include "core/collection/Map.h"
#include "core/Color.h"
#include "core/object/IntrusivePointer.h"
#include "core/object/SharedPointer.h"
#include "engine/graphics/texture/ITexture.h"
#include "ui/font/TextStyle.h"

namespace Ghurund::UI {

    typedef AttributeKey<Color> ColorKey;
    typedef AttributeKey<ITexture> TextureKey;
    typedef AttributeKey<Material> MaterialKey;
    typedef AttributeKey<Ghurund::UI::TextStyle> TextStyleKey;
    typedef AttributeKey<Control> LayoutKey;

    class Theme {
    private:
        static const inline float emphasis_high = 0.87f;
        static const inline float emphasis_medium = 0.6f;
        static const inline float emphasis_disabled = 0.38f;

        static const inline float highlight = 0.25f;

        static const inline float state_normal = 0.12f;
        //static const inline float state_activated = 0.4f;
        //static const inline float state_disabled = 0.08f;

        Ghurund::Core::Map<TextStyleKey, Ghurund::Core::IntrusivePointer<Ghurund::UI::TextStyle>> fonts;
        Ghurund::Core::Map<ColorKey, Color> colors;
        Ghurund::Core::Map<TextureKey, SharedPointer<TextureProvider>> textures;
        Ghurund::Core::Map<MaterialKey, SharedPointer<MaterialProvider>> materials;
        Ghurund::Core::Map<LayoutKey, SharedPointer<LayoutProvider>> layouts;

    public:
        static inline const TextureKey TEXTURE_CHECKBOX_CHECKED = TextureKey("checkBox_checked");
        static inline const TextureKey TEXTURE_CHECKBOX_UNCHECKED = TextureKey("checkBox_unchecked");
        static inline const TextureKey TEXTURE_RADIOBUTTON_CHECKED = TextureKey("radioButton_checked");
        static inline const TextureKey TEXTURE_RADIOBUTTON_UNCHECKED = TextureKey("radioButton_unchecked");
        static inline const TextureKey TEXTURE_ARROWUP = TextureKey("arrowUp");
        static inline const TextureKey TEXTURE_ARROWDOWN = TextureKey("arrowDown");
        static inline const TextureKey TEXTURE_ARROWRIGHT = TextureKey("arrowRight");

        static inline const TextStyleKey TEXT_STYLE_BUTTON = TextStyleKey("button");
        static inline const TextStyleKey TEXT_STYLE_LIST_HEADER = TextStyleKey("listHeader");
        static inline const TextStyleKey TEXT_STYLE_TEXT_PRIMARY = TextStyleKey("textPrimary");
        static inline const TextStyleKey TEXT_STYLE_TEXT_SECONDARY = TextStyleKey("textSecondary");

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

        static inline const MaterialKey MATERIAL_TEXT = MaterialKey("text");

        virtual ~Theme() {}

        void updateColors();

        inline Map<TextStyleKey, IntrusivePointer<Ghurund::UI::TextStyle>>& getTextFormats() {
            return fonts;
        }

        inline const Map<TextStyleKey, IntrusivePointer<Ghurund::UI::TextStyle>>& getTextFormats() const {
            return fonts;
        }

        __declspec(property(get = getTextFormats)) Map<TextStyleKey, IntrusivePointer<Ghurund::UI::TextStyle>>& TextStyles;

        inline Ghurund::Core::Map<ColorKey, Color>& getColors() {
            return colors;
        }

        inline const Ghurund::Core::Map<ColorKey, Color>& getColors() const {
            return colors;
        }

        __declspec(property(get = getColors)) Ghurund::Core::Map<ColorKey, Color>& Colors;

        inline Map<TextureKey, SharedPointer<TextureProvider>>& getTextures() {
            return textures;
        }

        inline const Map<TextureKey, SharedPointer<TextureProvider>>& getTextures() const {
            return textures;
        }

        __declspec(property(get = getTextures)) Map<TextureKey, SharedPointer<TextureProvider>>& Textures;

        inline Map<MaterialKey, SharedPointer<MaterialProvider>>& getMaterials() {
            return materials;
        }

        inline const Map<MaterialKey, SharedPointer<MaterialProvider>>& getMaterials() const {
            return materials;
        }

        __declspec(property(get = getMaterials)) Map<MaterialKey, SharedPointer<MaterialProvider>>& Materials;

        inline Ghurund::Core::Map<LayoutKey, SharedPointer<LayoutProvider>>& getLayouts() {
            return layouts;
        }

        inline const Ghurund::Core::Map<LayoutKey, SharedPointer<LayoutProvider>>& getLayouts() const {
            return layouts;
        }

        __declspec(property(get = getLayouts)) Ghurund::Core::Map<LayoutKey, SharedPointer<LayoutProvider>>& Layouts;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Theme>();
}