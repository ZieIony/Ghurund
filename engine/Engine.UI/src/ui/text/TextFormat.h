#pragma once

#include "Common.h"
#include "Status.h"
#include "core/Pointer.h"
#include "core/string/String.h"
#include "core/math/Size.h"

#include "ui/font/FontCollectionLoader.h"

struct IDWriteTextFormat;

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Canvas;
    class Control;

    class TextFormat:public Pointer {
    private:
        Font* font = nullptr;
        float size;
        bool italic = false, underline = false, strikethrough = false;
        uint32_t weight = 400, stretch = 0;
        Ghurund::Core::WString locale;
        IDWriteTextFormat* format = nullptr;

    protected:
        const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormat>(NAMESPACE_NAME, GH_STRINGIFY(TextFormat))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        TextFormat(Font* font, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
            :size(size), weight(weight), italic(italic), locale(locale) {
            this->font = font;
            font->addReference();
        }

        TextFormat(IDWriteTextFormat* format, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
            :size(size), weight(weight), italic(italic), locale(locale) {
            this->format = format;
            format->AddRef();
        }

        ~TextFormat();

        Status init(IDWriteFactory5& dwriteFactory);

        inline Font* getFont() {
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

        inline IDWriteTextFormat* getFormat() {
            return format;
        }

        __declspec(property(get = getFormat)) IDWriteTextFormat* Format;

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}