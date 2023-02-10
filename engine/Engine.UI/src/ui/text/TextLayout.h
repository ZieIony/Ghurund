#pragma once

#include "core/math/Size.h"
#include "core/string/String.h"
#include "ui/Color.h"
#include "TextMetrics.h"
#include "TextFormat.h"
#include "TextDocument.h"

namespace Ghurund::UI {
    class TextLayout {
    protected:
        Ghurund::Core::FloatSize size;
        Color color;
        Ghurund::UI::TextDocument* text;
        TextFormat* format = nullptr;

        bool valid = false;

    public:
        TextLayout(const Ghurund::Core::WString& text, const Color& color, TextFormat* format)
            :text(ghnew Ghurund::UI::TextDocument(text)), color(color) {
            Format = format;
        }

        virtual ~TextLayout() {
            if (format)
                format->release();
            delete text;
        }

        inline const Ghurund::UI::TextDocument& getText() const {
            return *text;
        }

        inline void setText(std::unique_ptr<Ghurund::UI::TextDocument> text) {
            if (this->text != text.get()) {
                delete this->text;
                this->text = text.release();
                valid = false;
            }
        }

        __declspec(property(get = getText, put = setText)) const Ghurund::UI::TextDocument& TextDocument;

        inline Ghurund::UI::TextFormat* getFormat() {
            return format;
        }

        inline void setFormat(Ghurund::UI::TextFormat* textFormat) {
            setPointer(this->format, (Ghurund::UI::TextFormat*)textFormat);
        }

        virtual Ghurund::UI::TextFormat* getFormat(uint32_t position) = 0;

        __declspec(property(get = getFormat, put = setFormat)) TextFormat* Format;

        inline void setColor(const Ghurund::UI::Color& color) {
            this->color = color;
        }

        inline const Ghurund::UI::Color& getColor() const {
            return color;
        }

        virtual Ghurund::UI::Color getColor(uint32_t pos) = 0;

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

        virtual TextMetrics getMetrics() = 0;

        __declspec(property(get = getMetrics)) TextMetrics TextMetrics;

        virtual Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics() = 0;

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        virtual Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics() = 0;

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        virtual HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY) = 0;

        virtual Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY) = 0;

        virtual HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit) = 0;

        inline void invalidate() {
            valid = false;
        }

        virtual Status refresh() = 0;

        virtual Status insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert) = 0;

        virtual Status removeTextAt(uint32_t position, uint32_t lengthToRemove) = 0;

        virtual void draw(ICanvas& canvas) = 0;
    };
}