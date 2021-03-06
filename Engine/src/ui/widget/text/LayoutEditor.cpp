#include "ghpch.h"
#include "LayoutEditor.h"

namespace Ghurund::UI {
    Status LayoutEditor::recreateLayout(IDWriteTextLayout*& currentLayout, const WString& text) {
        IDWriteTextLayout* newLayout = nullptr;

        if (FAILED(factory->CreateTextLayout(
            text.getData(),
            (UINT32)text.Length,
            currentLayout,
            currentLayout->GetMaxWidth(),
            currentLayout->GetMaxHeight(),
            &newLayout
        )))
            return Status::CALL_FAIL;

        if (currentLayout)
            currentLayout->Release();
        currentLayout = newLayout;

        return Status::OK;
    }

    void LayoutEditor::copySinglePropertyRange(IDWriteTextLayout* oldLayout, UINT32 startPosForOld, IDWriteTextLayout* newLayout, UINT32 startPosForNew, UINT32 length, TextFormat* textFormat) {
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
            newLayout->SetFontFamilyName(textFormat->FamilyName.Data, range);
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

            Array<wchar_t> localeName(LOCALE_NAME_MAX_LENGTH);
            localeName.set(0, '\0');
            oldLayout->GetLocaleName(startPosForOld, localeName.begin(), localeName.Size);
            newLayout->SetLocaleName(localeName.begin(), range);
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

    UINT32 LayoutEditor::calculateRangeLengthAt(IDWriteTextLayout* layout, UINT32 pos) {
        // Determines the length of a block of similarly formatted properties.

        // Use the first getter to get the range to increment the current position.
        DWRITE_TEXT_RANGE incrementAmount = { pos, 1 };
        DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL;

        layout->GetFontWeight(pos, &weight, &incrementAmount);

        return incrementAmount.length - (pos - incrementAmount.startPosition);
    }

    void LayoutEditor::copyRangedProperties(IDWriteTextLayout* oldLayout, UINT32 startPos, UINT32 endPos, UINT32 newLayoutTextOffset, IDWriteTextLayout* newLayout, bool isOffsetNegative) {
        UINT32 currentPos = startPos;
        while (currentPos < endPos) {
            UINT32 rangeLength = calculateRangeLengthAt(oldLayout, currentPos);
            rangeLength = std::min(rangeLength, endPos - currentPos);
            if (isOffsetNegative) {
                copySinglePropertyRange(oldLayout, currentPos, newLayout, currentPos - newLayoutTextOffset, rangeLength);
            } else {
                copySinglePropertyRange(oldLayout, currentPos, newLayout, currentPos + newLayoutTextOffset, rangeLength);
            }
            currentPos += rangeLength;
        }
    }

    Status LayoutEditor::insertTextAt(IDWriteTextLayout*& currentLayout, WString& text, UINT32 position, const WString& textToInsert, TextFormat* textFormat) {
        if (currentLayout)
            currentLayout->AddRef();
        IDWriteTextLayout* oldLayout = currentLayout;
        UINT32 oldTextLength = text.Length;
        position = std::min(position, (uint32_t)text.Size);

        text.insert(position, textToInsert.Data, textToInsert.Size);

        Status result = recreateLayout(currentLayout, text);

        IDWriteTextLayout* newLayout = currentLayout;

        if (result == Status::OK) {
            copyGlobalProperties(oldLayout, newLayout);

            // For each property, get the position range and apply it to the old text.
            if (position == 0) {
                // Inserted text
                copySinglePropertyRange(oldLayout, 0, newLayout, 0, textToInsert.Size);

                // The rest of the text
                copyRangedProperties(oldLayout, 0, oldTextLength, textToInsert.Size, newLayout);
            } else {
                // 1st block
                copyRangedProperties(oldLayout, 0, position, 0, newLayout);

                // Inserted text
                copySinglePropertyRange(oldLayout, position - 1, newLayout, position, textToInsert.Size, textFormat);

                // Last block (if it exists)
                copyRangedProperties(oldLayout, position, oldTextLength, textToInsert.Size, newLayout);
            }

            // Copy trailing end.
            copySinglePropertyRange(oldLayout, oldTextLength, newLayout, text.Length, UINT32_MAX);
        }

        if (oldLayout)
            oldLayout->Release();

        return result;
    }

    Status LayoutEditor::removeTextAt(IDWriteTextLayout*& currentLayout, WString& text, UINT32 position, UINT32 lengthToRemove) {
        if (currentLayout)
            currentLayout->AddRef();
        IDWriteTextLayout* oldLayout = currentLayout;
        UINT32 oldTextLength = text.Length;

        text.remove(position, lengthToRemove);

        Status result = recreateLayout(currentLayout, text);

        IDWriteTextLayout* newLayout = currentLayout;

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
            copySinglePropertyRange(oldLayout, oldTextLength, newLayout, text.Length, UINT32_MAX);
        }

        if (oldLayout)
            oldLayout->Release();

        return result;
    }

    void LayoutEditor::copyGlobalProperties(IDWriteTextLayout* oldLayout, IDWriteTextLayout* newLayout) {
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
}
