#pragma once

#include "Common.h"
#include "Status.h"
#include "core/Pointer.h"
#include "core/string/String.h"
#include "core/math/Size.h"
#include <ui/font/Font.h>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ICanvas;
    class Control;

    class TextFormat:public Pointer {
    private:
        Font* font = nullptr;
        float size;
        bool italic = false, underline = false, strikethrough = false;
        uint32_t weight = 400, stretch = 0;
        Ghurund::Core::WString locale;

    public:
        TextFormat(Font* font, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
            :size(size), weight(weight), italic(italic), locale(locale) {
            this->font = font;
            font->addReference();
        }

        ~TextFormat();

        inline const Font* getFont() const {
            return font;
        }

        __declspec(property(get = getFont)) Font* Font;

        inline float getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) float Size;

        inline bool isItalic() const {
            return italic;
        }

        __declspec(property(get = isItalic)) bool Italic;

        inline bool hasUnderline() const {
            return underline;
        }

        __declspec(property(get = hasUnderline)) bool Underline;

        inline bool hasStrikethrough() const {
            return strikethrough;
        }

        __declspec(property(get = hasStrikethrough)) bool Strikethrough;

        inline uint32_t getWeight() const {
            return weight;
        }

        __declspec(property(get = getWeight)) uint32_t Weight;

        inline uint32_t getStretch() const {
            return stretch;
        }

        __declspec(property(get = getStretch)) uint32_t Stretch;

        inline const Ghurund::Core::WString& getLocale() const {
            return locale;
        }

        __declspec(property(get = getLocale)) const Ghurund::Core::WString& Locale;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}