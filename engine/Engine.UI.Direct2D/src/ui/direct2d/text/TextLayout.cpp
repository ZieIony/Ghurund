#include "ghuidxpch.h"
#include "TextLayout.h"
#include "ui/direct2d/text/TextFormat.h"

namespace Ghurund::UI::Direct2D {
    Status TextLayout::refresh() {
        IDWriteTextLayout* newLayout = nullptr;

        IDWriteTextFormat* formatSource = nullptr;
        if (layout) {
            formatSource = layout;
        } else if (format) {
            formatSource = ((Ghurund::UI::Direct2D::TextFormat*)format)->Format;
        } else {
            return Status::INV_STATE;
        }

        if (FAILED(dwriteFactory.CreateTextLayout(text.Data, (uint32_t)text.Length, formatSource, size.Width, size.Height, &newLayout)))
            return Status::CALL_FAIL;

        if (layout)
            layout->Release();
        layout = newLayout;

        return Status::OK;
    }

    void TextLayout::copySinglePropertyRange(IDWriteTextLayout* oldLayout, uint32_t startPosForOld, IDWriteTextLayout* newLayout, uint32_t startPosForNew, uint32_t length, Ghurund::UI::Direct2D::TextFormat* textFormat) {
        // Copies a single range of similar properties, from one old layout
        // to a new one.

        DWRITE_TEXT_RANGE range = { startPosForNew,  std::min(length, UINT32_MAX - startPosForNew) };

        // font collection
        IDWriteFontCollection* fontCollection = nullptr;
        oldLayout->GetFontCollection(startPosForOld, &fontCollection);
        newLayout->SetFontCollection(fontCollection, range);
        if (fontCollection)
            fontCollection->Release();

        if (textFormat) {
            newLayout->SetFontFamilyName(textFormat->Font->FamilyName.Data, range);
            newLayout->SetLocaleName(textFormat->Locale.Data, range);
            newLayout->SetFontWeight((DWRITE_FONT_WEIGHT)textFormat->Weight, range);
            newLayout->SetFontStyle(textFormat->Italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL, range);
            //newLayout->SetFontStretch(font->fontStretch, range);
            newLayout->SetFontSize(textFormat->Size, range);
            //newLayout->SetUnderline(font->hasUnderline, range);
            //newLayout->SetStrikethrough(font->hasStrikethrough, range);
        } else {
            // font family
            wchar_t fontFamilyName[100];
            fontFamilyName[0] = '\0';
            oldLayout->GetFontFamilyName(startPosForOld, &fontFamilyName[0], ARRAYSIZE(fontFamilyName));
            newLayout->SetFontFamilyName(fontFamilyName, range);

            // weight/width/slope
            DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL;
            DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL;
            DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL;
            oldLayout->GetFontWeight(startPosForOld, &weight);
            oldLayout->GetFontStyle(startPosForOld, &style);
            oldLayout->GetFontStretch(startPosForOld, &stretch);

            newLayout->SetFontWeight(weight, range);
            newLayout->SetFontStyle(style, range);
            newLayout->SetFontStretch(stretch, range);

            FLOAT fontSize = 12.0;
            oldLayout->GetFontSize(startPosForOld, &fontSize);
            newLayout->SetFontSize(fontSize, range);

            BOOL value = FALSE;
            oldLayout->GetUnderline(startPosForOld, &value);
            newLayout->SetUnderline(value, range);
            oldLayout->GetStrikethrough(startPosForOld, &value);
            newLayout->SetStrikethrough(value, range);

            Ghurund::Core::Array<wchar_t> localeName(LOCALE_NAME_MAX_LENGTH);
            localeName.set(0, '\0');
            oldLayout->GetLocaleName(startPosForOld, &(*(localeName.begin())), (uint32_t)localeName.Size);
            newLayout->SetLocaleName(&(*(localeName.begin())), range);
        }

        // drawing effect
        IUnknown* drawingEffect = nullptr;
        oldLayout->GetDrawingEffect(startPosForOld, &drawingEffect);
        newLayout->SetDrawingEffect(drawingEffect, range);
        if (drawingEffect)
            drawingEffect->Release();

        // inline object
        IDWriteInlineObject* inlineObject = nullptr;
        oldLayout->GetInlineObject(startPosForOld, &inlineObject);
        newLayout->SetInlineObject(inlineObject, range);
        if (inlineObject)
            inlineObject->Release();

        // typography
        IDWriteTypography* typography = nullptr;
        oldLayout->GetTypography(startPosForOld, &typography);
        newLayout->SetTypography(typography, range);
        if (typography)
            typography->Release();
    }

    UINT32 TextLayout::calculateRangeLengthAt(IDWriteTextLayout* layout, UINT32 pos) {
        // Determines the length of a block of similarly formatted properties.

        // Use the first getter to get the range to increment the current position.
        DWRITE_TEXT_RANGE incrementAmount = { pos, 1 };
        DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL;

        layout->GetFontWeight(pos, &weight, &incrementAmount);

        return incrementAmount.length - (pos - incrementAmount.startPosition);
    }

    void TextLayout::copyRangedProperties(IDWriteTextLayout* oldLayout, uint32_t startPos, uint32_t endPos, uint32_t newLayoutTextOffset, IDWriteTextLayout* newLayout, bool isOffsetNegative) {
        uint32_t currentPos = startPos;
        while (currentPos < endPos) {
            uint32_t rangeLength = calculateRangeLengthAt(oldLayout, currentPos);
            rangeLength = std::min(rangeLength, endPos - currentPos);
            if (isOffsetNegative) {
                copySinglePropertyRange(oldLayout, currentPos, newLayout, currentPos - newLayoutTextOffset, rangeLength);
            } else {
                copySinglePropertyRange(oldLayout, currentPos, newLayout, currentPos + newLayoutTextOffset, rangeLength);
            }
            currentPos += rangeLength;
        }
    }

    HitTestMetrics TextLayout::hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY) {
        DWRITE_HIT_TEST_METRICS hitTestMetrics;
        layout->HitTestTextPosition(textPosition, isTrailingHit, pointX, pointY, &hitTestMetrics);
        return HitTestMetrics{
            hitTestMetrics.textPosition, hitTestMetrics.length, hitTestMetrics.left, hitTestMetrics.top, hitTestMetrics.width, hitTestMetrics.height
        };
    }

    Ghurund::Core::Array<HitTestMetrics> TextLayout::hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY) {
        UINT32 actualHitTestCount = 0;

        layout->HitTestTextRange(textPosition, textLength, 0, 0, nullptr, 0, &actualHitTestCount);

        Ghurund::Core::Array<DWRITE_HIT_TEST_METRICS> hitTestMetrics(actualHitTestCount);
        layout->HitTestTextRange(textPosition, textLength, 0, 0, &(*(hitTestMetrics.begin())), (UINT32)hitTestMetrics.Size, &actualHitTestCount);

        Ghurund::Core::Array<HitTestMetrics> hitTestMetrics2(actualHitTestCount);
        for (size_t i = 0; i < actualHitTestCount; i++) {
            hitTestMetrics2[i] = HitTestMetrics{
                hitTestMetrics[i].textPosition,
                hitTestMetrics[i].length,
                hitTestMetrics[i].left,
                hitTestMetrics[i].top,
                hitTestMetrics[i].width,
                hitTestMetrics[i].height
            };
        }

        return hitTestMetrics2;
    }

    HitTestMetrics TextLayout::hitTestPoint(float pointX, float pointY, bool* isTrailingHit) {
        DWRITE_HIT_TEST_METRICS hitTestMetrics;
        BOOL isTrailingHit2, isInside2;
        layout->HitTestPoint(pointX, pointY, &isTrailingHit2, &isInside2, &hitTestMetrics);
        return HitTestMetrics{
            hitTestMetrics.textPosition,
            hitTestMetrics.length,
            hitTestMetrics.left,
            hitTestMetrics.top,
            hitTestMetrics.width,
            hitTestMetrics.height
        };
        *isTrailingHit = isTrailingHit2 == TRUE;
    }

    Ghurund::Core::Array<Ghurund::UI::LineMetrics> TextLayout::getLineMetrics() {
        uint32_t lineCount = 0;
        layout->GetLineMetrics(nullptr, 0, &lineCount);
        Ghurund::Core::Array<DWRITE_LINE_METRICS> dwriteLineMetrics(lineCount);
        layout->GetLineMetrics(&(*(dwriteLineMetrics.begin())), lineCount, &lineCount);
        Ghurund::Core::Array<Ghurund::UI::LineMetrics> lineMetrics(lineCount);
        for (size_t i = 0; i < lineMetrics.Size; i++) {
            lineMetrics[i] = Ghurund::UI::LineMetrics{
                dwriteLineMetrics[i].length,
                dwriteLineMetrics[i].trailingWhitespaceLength,
                dwriteLineMetrics[i].newlineLength,
                dwriteLineMetrics[i].height,
                dwriteLineMetrics[i].baseline,
                dwriteLineMetrics[i].isTrimmed == TRUE
            };
        }
        return lineMetrics;
    }

    Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> TextLayout::getClusterMetrics() {
        UINT32 clusterCount;
        layout->GetClusterMetrics(nullptr, 0, &clusterCount);

        Ghurund::Core::Array<DWRITE_CLUSTER_METRICS> dwriteClusterMetrics(clusterCount);
        layout->GetClusterMetrics(&(*(dwriteClusterMetrics.begin())), clusterCount, &clusterCount);

        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> clusterMetrics(clusterCount);
        for (size_t i = 0; i < clusterMetrics.Size; i++) {
            clusterMetrics[i] = Ghurund::UI::ClusterMetrics{
                dwriteClusterMetrics[i].length,
                dwriteClusterMetrics[i].canWrapLineAfter == TRUE
            };
        }
        return clusterMetrics;
    }

    Status TextLayout::insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert) {
        if (layout)
            layout->AddRef();
        IDWriteTextLayout* oldLayout = layout;
        uint32_t oldTextLength = (uint32_t)text.Length;
        position = std::min(position, (uint32_t)text.Size);

        text.insert(position, textToInsert.Data, textToInsert.Size);

        Status result = refresh();

        IDWriteTextLayout* newLayout = layout;

        if (result == Status::OK) {
            copyGlobalProperties(oldLayout, newLayout);

            // For each property, get the position range and apply it to the old text.
            if (position == 0) {
                // Inserted text
                copySinglePropertyRange(oldLayout, 0, newLayout, 0, (uint32_t)textToInsert.Size);

                // The rest of the text
                copyRangedProperties(oldLayout, 0, oldTextLength, (uint32_t)textToInsert.Size, newLayout);
            } else {
                // 1st block
                copyRangedProperties(oldLayout, 0, position, 0, newLayout);

                // Inserted text
                copySinglePropertyRange(oldLayout, position - 1, newLayout, position, (uint32_t)textToInsert.Size, (Ghurund::UI::Direct2D::TextFormat*)format);

                // Last block (if it exists)
                copyRangedProperties(oldLayout, position, oldTextLength, (uint32_t)textToInsert.Size, newLayout);
            }

            // Copy trailing end.
            copySinglePropertyRange(oldLayout, oldTextLength, newLayout, (uint32_t)text.Length, UINT32_MAX);
        }

        if (oldLayout)
            oldLayout->Release();

        return result;
    }

    Status TextLayout::removeTextAt(uint32_t position, uint32_t lengthToRemove) {
        if (layout)
            layout->AddRef();
        IDWriteTextLayout* oldLayout = layout;
        uint32_t oldTextLength = (uint32_t)text.Length;

        text.remove(position, lengthToRemove);

        Status result = refresh();

        IDWriteTextLayout* newLayout = layout;

        if (result == Status::OK) {
            copyGlobalProperties(oldLayout, newLayout);

            if (position == 0) {
                // The rest of the text
                copyRangedProperties(oldLayout, lengthToRemove, oldTextLength, lengthToRemove, newLayout, true);
            } else {
                // 1st block
                copyRangedProperties(oldLayout, 0, position, 0, newLayout, true);

                // Last block (if it exists, we increment past the deleted text)
                copyRangedProperties(oldLayout, position + lengthToRemove, oldTextLength, lengthToRemove, newLayout, true);
            }
            copySinglePropertyRange(oldLayout, oldTextLength, newLayout, (uint32_t)text.Length, UINT32_MAX);
        }

        if (oldLayout)
            oldLayout->Release();

        return result;
    }

    void TextLayout::copyGlobalProperties(IDWriteTextLayout* oldLayout, IDWriteTextLayout* newLayout) {
        newLayout->SetTextAlignment(oldLayout->GetTextAlignment());
        newLayout->SetParagraphAlignment(oldLayout->GetParagraphAlignment());
        newLayout->SetWordWrapping(oldLayout->GetWordWrapping());
        newLayout->SetReadingDirection(oldLayout->GetReadingDirection());
        newLayout->SetFlowDirection(oldLayout->GetFlowDirection());
        newLayout->SetIncrementalTabStop(oldLayout->GetIncrementalTabStop());

        DWRITE_TRIMMING trimmingOptions = {};
        IDWriteInlineObject* inlineObject = nullptr;
        oldLayout->GetTrimming(&trimmingOptions, &inlineObject);
        newLayout->SetTrimming(&trimmingOptions, inlineObject);
        if (inlineObject)
            inlineObject->Release();

        DWRITE_LINE_SPACING_METHOD lineSpacingMethod = DWRITE_LINE_SPACING_METHOD_DEFAULT;
        FLOAT lineSpacing = 0;
        FLOAT baseline = 0;
        oldLayout->GetLineSpacing(&lineSpacingMethod, &lineSpacing, &baseline);
        newLayout->SetLineSpacing(lineSpacingMethod, lineSpacing, baseline);
    }

    Ghurund::UI::Color TextLayout::getColor(uint32_t pos) {
        IUnknown* effect;
        layout->GetDrawingEffect(pos, &effect);
        if (effect) {
            Ghurund::UI::Color color = ((TextPaint*)effect)->Color;
            effect->Release();
            return color;
        }
        return Color;
    }

    Ghurund::UI::TextFormat* TextLayout::getFormat(uint32_t position) {
        Ghurund::Core::Array<wchar_t> fontFamilyName(100);
        fontFamilyName.set(0, L'\0');
        layout->GetFontFamilyName(position, &(*(fontFamilyName.begin())), (UINT32)fontFamilyName.Size);

        Ghurund::Core::Array<wchar_t> localeName(LOCALE_NAME_MAX_LENGTH);
        localeName.set(0, L'\0');
        layout->GetLocaleName(position, &(*(localeName.begin())), (UINT32)localeName.Size);

        DWRITE_FONT_WEIGHT fontWeight;
        layout->GetFontWeight(position, &fontWeight);

        DWRITE_FONT_STYLE fontStyle;
        layout->GetFontStyle(position, &fontStyle);

        DWRITE_FONT_STRETCH fontStretch;
        layout->GetFontStretch(position, &fontStretch);
        //stretch = (DWRITE_FONT_STRETCH)fontStretch;

        float size;
        layout->GetFontSize(position, &size);

        BOOL hasUnderline;
        layout->GetUnderline(position, &hasUnderline);
        //underline = hasUnderline;

        BOOL hasStrikethrough;
        layout->GetStrikethrough(position, &hasStrikethrough);
        //strikethrough = hasStrikethrough;

        // TODO: this method returns a new Pointer object
        return ghnew Ghurund::UI::Direct2D::TextFormat(layout, size, fontWeight, fontStyle == DWRITE_FONT_STYLE_ITALIC, &(*(localeName.begin())));
    }

    TextMetrics TextLayout::getMetrics() {
        DWRITE_TEXT_METRICS dwriteMetrics;
        layout->GetMetrics(&dwriteMetrics);
        return Ghurund::UI::TextMetrics{
            dwriteMetrics.left, dwriteMetrics.top, dwriteMetrics.width, dwriteMetrics.height,
            dwriteMetrics.widthIncludingTrailingWhitespace,
            dwriteMetrics.layoutWidth, dwriteMetrics.layoutHeight,
            dwriteMetrics.maxBidiReorderingDepth,
            dwriteMetrics.lineCount
        };
    }
}
