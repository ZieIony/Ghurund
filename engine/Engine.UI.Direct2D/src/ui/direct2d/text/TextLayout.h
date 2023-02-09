#pragma once

#include "ui/text/TextLayout.h"
#include "ui/text/TextMetrics.h"
#include "ui/direct2d/text/TextFormat.h"
#include "core/math/Size.h"
#include "ui/Canvas.h"
#include "core/IUnknownImpl.h"

#include <d2d1.h>
#include <wrl.h>
#include <ui/Color.h>
#include <d2d1_3.h>

namespace Ghurund::UI::Direct2D {
    using namespace Microsoft::WRL;

    class TextLayout:public Ghurund::UI::TextLayout {
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

        IDWriteFactory& dwriteFactory;
        ComPtr<ID2D1SolidColorBrush> fillBrush;
        IDWriteTextLayout* layout = nullptr;

        void copySinglePropertyRange(IDWriteTextLayout* oldLayout, uint32_t startPosForOld, IDWriteTextLayout* newLayout, uint32_t startPosForNew, uint32_t length, Ghurund::UI::Direct2D::TextFormat* textFormat = nullptr);

        uint32_t calculateRangeLengthAt(IDWriteTextLayout* layout, uint32_t pos);

        void copyRangedProperties(IDWriteTextLayout* oldLayout, uint32_t startPos, uint32_t afterEndPos, uint32_t newLayoutTextOffset, IDWriteTextLayout* newLayout, bool isOffsetNegative = false);

        void copyGlobalProperties(IDWriteTextLayout* oldLayout, IDWriteTextLayout* newLayout);

    public:
        TextLayout(IDWriteFactory& dwriteFactory, const Ghurund::Core::WString& text, const Ghurund::UI::Color& color, Ghurund::UI::Direct2D::TextFormat* format)
            :Ghurund::UI::TextLayout(text, color, format), dwriteFactory(dwriteFactory) {}

        virtual Ghurund::UI::Color getColor(uint32_t pos) override;

        Ghurund::UI::TextFormat* getFormat(uint32_t position);

        Ghurund::UI::TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) Ghurund::UI::TextMetrics TextMetrics;

        Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        Status refresh();

        inline IDWriteTextLayout* get() {
            return layout;
        }

        Status insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        Status removeTextAt(uint32_t position, uint32_t lengthToRemove);
    };
}