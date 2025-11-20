#pragma once

#include "TextFormat.h"
#include "core/Color.h"
#include "core/object/IntrusivePointer.h"
#include "core/string/TextConversionUtils.h"
#include "ui/drawable/Drawable.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    class LayoutLoader;

    struct DocumentElement {
        FloatSize size;

        virtual size_t getLength() const = 0;

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) = 0;

        virtual void draw(RenderGroup& group, const TextFormat& parentFormat, const Color& color) const = 0;
    };

    struct DocumentElementGroup:public DocumentElement {
        List<DocumentElement*> elements;

        virtual size_t getLength() const override {
            size_t length = 0;
            for (auto element : elements)
                length += element->getLength();
            return length;
        }

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        virtual void draw(RenderGroup& group, const TextFormat& parentFormat, const Color& color) const override {
            for (auto element : elements)
                element->draw(group, parentFormat, color);
        }
    };

    class TextElement:public DocumentElement {
    private:
        WString text;

    public:
        TextElement(const WString& text):text(text) {}

        virtual size_t getLength() const override {
            return text.Length;
        }

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            text = convertText<char, wchar_t>(AString(xml.Value()));
        }

        virtual void draw(RenderGroup& group, const TextFormat& parentFormat, const Color& color) const override {

        }
    };

    struct DrawableElement:public DocumentElement {
        Drawable* drawable;

        virtual size_t getLength() const override {
            return 1;
        }

        virtual void draw(RenderGroup& group, const TextFormat& parentFormat, const Color& color) const override {
            //drawable->draw(canvas);
        }
    };

    struct BoldSpan:public DocumentElementGroup {
        IntrusivePointer<TextFormat> textFormat;

        BoldSpan(Font* font, float size, bool italic, WString& locale):textFormat(makeIntrusive<TextFormat>(font, size, FW_BOLD, italic, locale)) {}

        virtual void draw(RenderGroup& group, const TextFormat& parentFormat, const Color& color) const override {
            __super::draw(group, *textFormat.get(), color);
        }
    };

    struct ItalicSpan:public DocumentElementGroup {
        IntrusivePointer<TextFormat> textFormat;

        ItalicSpan(Font* font, float size, uint32_t weight, WString& locale):textFormat(makeIntrusive<TextFormat>(font, size, weight, true, locale)) {}

        virtual void draw(RenderGroup& group, const TextFormat& parentFormat, const Color& color) const override {
            __super::draw(group, *textFormat.get(), color);
        }
    };

    struct ColorSpan:public DocumentElementGroup {
        Color color;

        virtual void draw(RenderGroup& group, const TextFormat& parentFormat, const Color& color) const override {
            __super::draw(group, parentFormat, this->color);
        }
    };

    struct Paragraph {

    };

    struct DrawableSpan {

    };
}