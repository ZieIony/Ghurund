#include "ghuipch.h"
#include "ThemedValue.h"

#include "Theme.h"

namespace Ghurund::UI {
    template<>
    IntrusivePointer<ITexture> resolveThemeValue(const Theme& theme, const TextureKey& key) {
        return theme.Textures[key]->get();
    }

    template<>
    Color resolveThemeValue(const Theme& theme, const ColorKey& key) {
        return theme.Colors[key];
    }

    template<>
    IntrusivePointer<TextStyle> resolveThemeValue(const Theme& theme, const TextStyleKey& key) {
        return theme.TextStyles[key];
    }
}

namespace Ghurund::Core {

    template<>
    const Type& getType<Ghurund::UI::ThemedTexture>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ThemedTexture>();
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::UI::ThemedColor>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ThemedColor>();
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::UI::ThemedTextStyle>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ThemedTextStyle>();
        return TYPE;
    }
}