#pragma once

#include "TextFormat.h"
#include "core/SharedPointer.h"
#include "ui/Color.h"
#include "ui/drawable/Drawable.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    class LayoutLoader;
    class ICanvas;

    struct DocumentElement {
        FloatSize size;

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) = 0;

        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const = 0;
    };

    struct DocumentElementGroup:public DocumentElement {
        List<DocumentElement*> elements;

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {
            for (auto element : elements)
                element->draw(canvas, parentFormat, color);
        }
    };

    class TextElement:public DocumentElement {
    private:
        WString text;

    public:
        TextElement(const WString& text):text(text) {}

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            text = convertText<char, wchar_t>(AString(xml.Value()));
        }

        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {

        }
    };

    struct DrawableElement:public DocumentElement {
        Drawable* drawable;

        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {
            drawable->draw(canvas);
        }
    };

    struct BoldSpan:public DocumentElementGroup {
        SharedPointer<TextFormat> textFormat;

        BoldSpan(Font* font, float size, bool italic, WString& locale):textFormat(makeShared<TextFormat>(font, size, FW_BOLD, italic, locale)) {}

        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {
            __super::draw(canvas, *textFormat.get(), color);
        }
    };

    struct ItalicSpan:public DocumentElementGroup {
        SharedPointer<TextFormat> textFormat;

        ItalicSpan(Font* font, float size, uint32_t weight, WString& locale):textFormat(makeShared<TextFormat>(font, size, weight, true, locale)) {}

        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {
            __super::draw(canvas, *textFormat.get(), color);
        }
    };

    struct ColorSpan:public DocumentElementGroup {
        Color color;

        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {
            __super::draw(canvas, parentFormat, this->color);
        }
    };

    struct Paragraph {

    };

    struct DrawableSpan {

    };
}