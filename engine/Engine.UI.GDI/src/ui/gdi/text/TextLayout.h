#pragma once

#include "ui/text/ITextLayout.h"
#include "ui/text/TextMetrics.h"
#include "ui/gdi/text/TextFormat.h"
#include "core/math/Size.h"
#include "ui/Canvas.h"
#include "core/IUnknownImpl.h"

#include <d2d1.h>
#include <wrl.h>
#include <ui/Color.h>
#include <gdiplus.h>

namespace Ghurund::UI::GDI {
    using namespace Microsoft::WRL;

    class TextLayout:public ITextLayout {
    private:
        class DECLSPEC_UUID("1CD7C44F-526B-492a-B780-EF9C4159B653") TextPaint: public Ghurund::Core::ComBase<QiList<IUnknown>> {
        private:
            uint32_t color;

        public:
            TextPaint(uint32_t color): color(color) {}

            inline uint32_t getColor() const throw() {
                return color;
            }

            __declspec(property(get = getColor)) uint32_t Color;
        };

        Ghurund::Core::FloatSize size;
        Ghurund::UI::Color color;
        Ghurund::Core::WString text;
        Ghurund::UI::GDI::TextFormat* format = nullptr;

        IDWriteFactory& dwriteFactory;
        ComPtr<ID2D1SolidColorBrush> fillBrush;
        IDWriteTextLayout* layout = nullptr;
        bool valid = false;

        void copySinglePropertyRange(IDWriteTextLayout* oldLayout, uint32_t startPosForOld, IDWriteTextLayout* newLayout, uint32_t startPosForNew, uint32_t length, Ghurund::UI::GDI::TextFormat* textFormat = nullptr);

        uint32_t calculateRangeLengthAt(IDWriteTextLayout* layout, uint32_t pos);

        void copyRangedProperties(IDWriteTextLayout* oldLayout, uint32_t startPos, uint32_t afterEndPos, uint32_t newLayoutTextOffset, IDWriteTextLayout* newLayout, bool isOffsetNegative = false);

        void copyGlobalProperties(IDWriteTextLayout* oldLayout, IDWriteTextLayout* newLayout);

    public:
        TextLayout(IDWriteFactory& dwriteFactory, const Ghurund::Core::WString& text, const Ghurund::UI::Color& color, Ghurund::UI::GDI::TextFormat* format)
            :dwriteFactory(dwriteFactory), text(text), color(color) {
            Format = format;
        }

        ~TextLayout() {
            if (format)
                format->release();
        }

        inline const Ghurund::Core::FloatSize& getSize() const {
            return size;
        }

        inline void setSize(const Ghurund::Core::FloatSize& size) {
            setSize(size.width, size.height);
        }

        virtual void setSize(float w, float h) {
            if (size.width != w || size.height != h) {
                size = { w, h };
                valid = false;
            }
        }

        __declspec(property(get = getSize, put = setSize)) const Ghurund::Core::FloatSize& Size;

        inline void setColor(const Ghurund::UI::Color& color) {
            this->color = color;
        }

        inline const Ghurund::UI::Color& getColor() const {
            return color;
        }

        __declspec(property(get = getColor, put = setColor)) const Ghurund::UI::Color& Color;

        Ghurund::UI::Color getColor(uint32_t pos);

        inline const Ghurund::Core::WString& getText() const {
            return text;
        }

        inline void setText(const Ghurund::Core::WString& text) {
            if (this->text != text) {
                this->text = text;
                valid = false;
            }
        }

        __declspec(property(get = getText, put = setText)) const Ghurund::Core::WString& Text;

        inline Ghurund::UI::TextFormat* getFormat() {
            return format;
        }

        inline void setFormat(Ghurund::UI::TextFormat* textFormat) {
            setPointer(this->format, (Ghurund::UI::GDI::TextFormat*)textFormat);
        }

        __declspec(property(get = getFormat, put = setFormat)) Ghurund::UI::TextFormat* Format;

        Ghurund::UI::TextFormat* getFormat(uint32_t position);

        Ghurund::UI::TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) Ghurund::UI::TextMetrics TextMetrics;

        Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();;

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        inline void invalidate() {
            valid = false;
        }

        Status refresh();

        Status insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        Status removeTextAt(uint32_t position, uint32_t lengthToRemove);
    };
}