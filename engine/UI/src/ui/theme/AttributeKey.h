#pragma once

#include "core/Color.h"
#include "core/string/String.h"
#include "engine/graphics/texture/ITexture.h"
#include "ui/font/TextStyle.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    template<typename Type>
    class AttributeKey {
    private:
        Ghurund::Core::AString str;

    public:
        AttributeKey(const Ghurund::Core::AString& str):str(str) {}

        const Ghurund::Core::AString& getValue() const {
            return str;
        }

        __declspec(property(get = getValue)) const Ghurund::Core::AString& Value;

        inline constexpr std::strong_ordering operator<=>(const AttributeKey& other) const noexcept {
            return str <=> other.str;
        }
    };

    using ColorKey = AttributeKey<Color>;
    using TextureKey = AttributeKey<ITexture>;
    using TextStyleKey = AttributeKey<Ghurund::UI::TextStyle>;
}