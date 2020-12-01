#pragma once

#include "CaretFormat.h"
#include "DrawingEffect.h"
#include "SetSelectionMode.h"
#include "ui/control/TextBlock.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    class TextView:public TextBlock {
    private:
        DrawingEffect* textSelectionEffect;
        DrawingEffect* imageSelectionEffect;
        DrawingEffect* caretBackgroundEffect;

    protected:
        uint32_t caretAnchor = 0;
        uint32_t caretPosition = 0;
        uint32_t caretPositionOffset = 0;
        CaretFormat caretFormat;

        DWRITE_TEXT_RANGE getSelectionRange();

        D2D1_RECT_F getCaretRect();

        void getLineMetrics(std::vector<DWRITE_LINE_METRICS>& lineMetrics);

        void getLineFromPosition(const DWRITE_LINE_METRICS* lineMetrics, UINT32 lineCount, UINT32 textPosition, UINT32* lineOut, UINT32* linePositionOut);

        void alignCaretToNearestCluster(bool isTrailingHit, bool skipZeroWidth);

        void updateCaretFormatting();

        void updateSystemCaret(const D2D1_RECT_F& rect);

        bool setSelectionFromPoint(float x, float y, bool extendSelection);

    public:
        TextView(Theme& theme):TextBlock("", theme.getPrimaryTextFont(), theme.getColorForegroundPrimaryOnBackground()) {
            textSelectionEffect = ghnew DrawingEffect(theme.ColorHighlightOnBackground);
            imageSelectionEffect = ghnew DrawingEffect(theme.ColorHighlightOnBackground);
            caretBackgroundEffect = ghnew DrawingEffect(theme.getColorForegroundPrimaryOnBackground());
            updateCaretFormatting();
        }

        ~TextView() {
            textSelectionEffect->Release();
            imageSelectionEffect->Release();
            caretBackgroundEffect->Release();
        }

        bool setSelection(SetSelectionMode moveMode, UINT32 advance, bool extendSelection, bool updateCaretFormat = true);

        virtual void onDraw(Canvas& canvas) override;
    };
}