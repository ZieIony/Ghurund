#pragma once

#include "core/Color.h"
#include "core/object/IntrusivePointer.h"
#include "core/string/TextConversionUtils.h"
#include "engine/graphics/rendering/RenderGroup.h"
#include "ui/font/Font.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class LayoutLoader;

    struct DocumentElement {
        FloatSize size;

        virtual size_t getLength() const = 0;

        virtual void load(Ghurund::UI::LayoutLoader& loader, const XMLElement& xml) = 0;

        virtual void draw(RenderGroup& group, const Font& parentFormat, const Color& color) const = 0;
    };

    struct DocumentElementGroup:public DocumentElement {
        List<DocumentElement*> elements;

        virtual size_t getLength() const override {
            size_t length = 0;
            for (auto element : elements)
                length += element->getLength();
            return length;
        }

        virtual void load(Ghurund::UI::LayoutLoader& loader, const XMLElement& xml) override;

        virtual void draw(RenderGroup& group, const Font& parentFormat, const Color& color) const override {
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

        virtual void load(Ghurund::UI::LayoutLoader& loader, const XMLElement& xml) override {
            //text = convertText<char, wchar_t>(AString(xml.Value()));
        }

        virtual void draw(RenderGroup& group, const Font& parentFormat, const Color& color) const override {

        }
    };

    struct DrawableElement:public DocumentElement {
        //Drawable* drawable;

        virtual size_t getLength() const override {
            return 1;
        }

        virtual void draw(RenderGroup& group, const Font& parentFormat, const Color& color) const override {
            //drawable->draw(canvas);
        }
    };

    struct BoldSpan:public DocumentElementGroup {
        IntrusivePointer<Font> font;

        BoldSpan(Font* font, float size, bool italic):font(font) {
            font->addReference();
        }

        virtual void draw(RenderGroup& group, const Font& parentFormat, const Color& color) const override {
            __super::draw(group, *font.get(), color);
        }
    };

    struct ItalicSpan:public DocumentElementGroup {
        IntrusivePointer<Font> font;

        ItalicSpan(Font* font, float size, uint32_t weight):font(font) {
            font->addReference();
        }

        virtual void draw(RenderGroup& group, const Font& parentFormat, const Color& color) const override {
            __super::draw(group, *font.get(), color);
        }
    };

    struct ColorSpan:public DocumentElementGroup {
        Color color;

        virtual void draw(RenderGroup& group, const Font& parentFormat, const Color& color) const override {
            __super::draw(group, parentFormat, this->color);
        }
    };

    struct Paragraph {

    };

    struct DrawableSpan {

    };
}
