#pragma once

#include "core/Color.h"
#include "core/math/Size.h"
#include "core/string/String.h"
#include "TextMetrics.h"
#include "TextFormat.h"
#include "TextDocument.h"

namespace Ghurund::UI {
    struct CharacterInfo {
        wchar_t c;
        size_t index;
        XMFLOAT2 pos;
        GlyphMetrics glyph;
        Color color;
        TextFormat* format;
    };

    class TextLayout {
    protected:
        Ghurund::Core::FloatSize size;
        Color color;
        Ghurund::UI::TextDocument text = Ghurund::UI::TextDocument(L"");
        TextFormat* format = nullptr;
        List<List<CharacterInfo>> lines;

        bool valid = false;

        void breakLine(List<CharacterInfo>& line);

    public:
        TextLayout() {}

        TextLayout(const Ghurund::Core::WString& text, const Color& color, TextFormat* format)
            :text(Ghurund::UI::TextDocument(text)), color(color) {
            Format = format;
        }

        virtual ~TextLayout() {
            if (format)
                format->release();
        }

        inline const Ghurund::UI::TextDocument& getText() const {
            return text;
        }

        inline void setText(const Ghurund::UI::TextDocument& text) {
            if (this->text != text) {
                this->text = text;
                valid = false;
            }
        }

        __declspec(property(get = getText, put = setText)) const Ghurund::UI::TextDocument& TextDocument;

        inline Ghurund::UI::TextFormat* getFormat() {
            return format;
        }

        inline void setFormat(const Ghurund::UI::TextFormat* textFormat) {
            setPointer(this->format, (Ghurund::UI::TextFormat*)textFormat);
        }

        virtual Ghurund::UI::TextFormat* getFormat(uint32_t position);

        __declspec(property(get = getFormat, put = setFormat)) TextFormat* Format;

        inline void setColor(const Ghurund::UI::Color& color) {
            this->color = color;
        }

        inline const Ghurund::Core::Color& getColor() const {
            return color;
        }

        virtual Ghurund::Core::Color getColor(uint32_t pos);

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        inline const Ghurund::Core::FloatSize& getSize() const {
            return size;
        }

        inline void setSize(const Ghurund::Core::FloatSize& size) {
            setSize(size.Width, size.Height);
        }

        inline void setSize(float w, float h) {
            if (size.Width != w || size.Height != h) {
                size = { w, h };
                valid = false;
            }
        }

        __declspec(property(get = getSize, put = setSize)) const Ghurund::Core::FloatSize& Size;

        virtual TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) TextMetrics TextMetrics;

        virtual Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        virtual Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        virtual HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        virtual Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        virtual HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        inline void invalidate() {
            valid = false;
        }

        virtual void refresh();

        virtual void insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        virtual void removeTextAt(uint32_t position, uint32_t lengthToRemove);

        virtual void draw(RenderGroup& group);

        uint32_t measureWidth();

        uint32_t measureHeight();
    };
}