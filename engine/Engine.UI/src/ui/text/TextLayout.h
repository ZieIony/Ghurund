#pragma once

#include "TextMetrics.h"
#include "TextFormat.h"
#include "core/math/Size.h"
#include "ui/Canvas.h"
#include "ui/text/DrawingEffect.h"

#include <d2d1.h>
#include <wrl.h>
#include <ui/Color.h>
#include <d2d1_3.h>

namespace Ghurund::UI {
    using namespace Microsoft::WRL;

    class TextLayout {
    private:
        IntSize size;
        Color color;
        WString text;
        TextFormat* format = nullptr;

        ComPtr<ID2D1SolidColorBrush> fillBrush;
        IDWriteTextLayout* layout = nullptr;
        bool valid = false;

        void copySinglePropertyRange(IDWriteTextLayout* oldLayout, uint32_t startPosForOld, IDWriteTextLayout* newLayout, uint32_t startPosForNew, uint32_t length, TextFormat* textFormat = nullptr);

        uint32_t calculateRangeLengthAt(IDWriteTextLayout* layout, uint32_t pos);

        void copyRangedProperties(IDWriteTextLayout* oldLayout, uint32_t startPos, uint32_t afterEndPos, uint32_t newLayoutTextOffset, IDWriteTextLayout* newLayout, bool isOffsetNegative = false);

        void copyGlobalProperties(IDWriteTextLayout* oldLayout, IDWriteTextLayout* newLayout);

    public:
        TextLayout(const WString& text, const Color& color, TextFormat* format):text(text), color(color) {
            Format = format;
        }

        ~TextLayout() {
            if (format)
                format->release();
        }

        inline const IntSize& getSize() const {
            return size;
        }

        inline void setSize(const IntSize& size) {
            setSize(size.width, size.height);
        }

        virtual void setSize(uint32_t w, uint32_t h) {
            if (size.width != w || size.height != h) {
                size = { w, h };
                valid = false;
            }
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

        inline void setColor(const Color& color) {
            this->color = color;
        }

        inline const Color& getColor() const {
            return color;
        }

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        Ghurund::UI::Color getColor(uint32_t pos);

        inline const WString& getText() const {
            return text;
        }

        inline void setText(const WString& text) {
            if (this->text != text) {
                this->text = text;
                valid = false;
            }
        }

        __declspec(property(get = getText, put = setText)) const WString& Text;

        inline TextFormat* getFormat() {
            return format;
        }

        inline void setFormat(TextFormat* textFormat) {
            setPointer(this->format, textFormat);
        }

        __declspec(property(get = getFormat, put = setFormat)) TextFormat* Format;

        Ghurund::UI::TextFormat* getFormat(uint32_t position);

        TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) TextMetrics TextMetrics;

        HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Array<Ghurund::UI::LineMetrics> LineMetrics;

        Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();;

        __declspec(property(get = getClusterMetrics)) Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        inline void invalidate() {
            valid = false;
        }

        Status buildLayout(IDWriteFactory& dwriteFactory);

        inline void draw(Canvas& canvas, float x, float y) {
            canvas.drawText(*layout, x, y, color);
        }

        Status insertTextAt(IDWriteFactory& dwriteFactory, uint32_t position, const WString& textToInsert);

        Status removeTextAt(IDWriteFactory& dwriteFactory, uint32_t position, uint32_t lengthToRemove);
    };
}