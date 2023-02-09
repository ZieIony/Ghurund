#pragma once

#include "core/SharedPointer.h"
#include "ui/Canvas.h"
#include "ui/Color.h"
#include "ui/drawable/Drawable.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    class LayoutLoader;

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

    struct TextElement:public DocumentElement {
        WString text;

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
        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {
            auto format = makeShared<TextFormat>(parentFormat.Font, parentFormat.Size, FW_BOLD, parentFormat.Italic, parentFormat.Locale);
            __super::draw(canvas, *format.get(), color);
        }
    };

    struct ItalicSpan:public DocumentElementGroup {
        virtual void draw(ICanvas& canvas, const TextFormat& parentFormat, const Color& color) const override {
            auto format = makeShared<TextFormat>(parentFormat.Font, parentFormat.Size, parentFormat.Weight, true, parentFormat.Locale);
            __super::draw(canvas, *format.get(), color);
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