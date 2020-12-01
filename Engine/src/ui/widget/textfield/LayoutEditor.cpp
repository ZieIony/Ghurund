#include "LayoutEditor.h"

namespace Ghurund::UI {
    HRESULT LayoutEditor::recreateLayout(IDWriteTextLayout*& currentLayout, const UnicodeString& text) {
        HRESULT hr = S_OK;

        IDWriteTextLayout* newLayout = nullptr;

        hr = factory->CreateTextLayout(
            text.getData(),
            (UINT32)text.Length,
            currentLayout,
            currentLayout->GetMaxWidth(),
            currentLayout->GetMaxHeight(),
            &newLayout
        );

        if (SUCCEEDED(hr)) {
            if (currentLayout)
                currentLayout->Release();
            currentLayout = newLayout;
        }

        return hr;
    }
    
    void LayoutEditor::copySinglePropertyRange(IDWriteTextLayout* oldLayout, UINT32 startPosForOld, IDWriteTextLayout* newLayout, UINT32 startPosForNew, UINT32 length, CaretFormat* caretFormat) {
        // Copies a single range of similar properties, from one old layout
        // to a new one.

        DWRITE_TEXT_RANGE range = { startPosForNew,  std::min(length, UINT32_MAX - startPosForNew) };

        // font collection
        IDWriteFontCollection* fontCollection = nullptr;
        oldLayout->GetFontCollection(startPosForOld, &fontCollection);
        newLayout->SetFontCollection(fontCollection, range);
        if (fontCollection)
            fontCollection->Release();

        if (caretFormat) {
            newLayout->SetFontFamilyName(caretFormat->fontFamilyName, range);
            newLayout->SetLocaleName(caretFormat->localeName, range);
            newLayout->SetFontWeight(caretFormat->fontWeight, range);
            newLayout->SetFontStyle(caretFormat->fontStyle, range);
            newLayout->SetFontStretch(caretFormat->fontStretch, range);
            newLayout->SetFontSize(caretFormat->fontSize, range);
            newLayout->SetUnderline(caretFormat->hasUnderline, range);
            newLayout->SetStrikethrough(caretFormat->hasStrikethrough, range);
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

            // font size
            FLOAT fontSize = 12.0;
            oldLayout->GetFontSize(startPosForOld, &fontSize);
            newLayout->SetFontSize(fontSize, range);

            // underline and strikethrough
            BOOL value = FALSE;
            oldLayout->GetUnderline(startPosForOld, &value);
            newLayout->SetUnderline(value, range);
            oldLayout->GetStrikethrough(startPosForOld, &value);
            newLayout->SetStrikethrough(value, range);

            // locale
            wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
            localeName[0] = '\0';
            oldLayout->GetLocaleName(startPosForOld, &localeName[0], ARRAYSIZE(localeName));
            newLayout->SetLocaleName(localeName, range);
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

        layout->GetFontWeight(pos,&weight,&incrementAmount);

        UINT32 rangeLength = incrementAmount.length - (pos - incrementAmount.startPosition);
        return rangeLength;
    }
    
    void LayoutEditor::copyRangedProperties(IDWriteTextLayout* oldLayout, UINT32 startPos, UINT32 endPos, UINT32 newLayoutTextOffset, IDWriteTextLayout* newLayout, bool isOffsetNegative) {
        // Copies properties that set on ranges.

        UINT32 currentPos = startPos;
        while (currentPos < endPos) {
            UINT32 rangeLength = calculateRangeLengthAt(oldLayout, currentPos);
            rangeLength = std::min(rangeLength, endPos - currentPos);
            if (isOffsetNegative) {
                copySinglePropertyRange(oldLayout,currentPos,newLayout,currentPos - newLayoutTextOffset,rangeLength);
            } else {
                copySinglePropertyRange(oldLayout,currentPos,newLayout,currentPos + newLayoutTextOffset,rangeLength);
            }
            currentPos += rangeLength;
        }
    }
    
    HRESULT LayoutEditor::insertTextAt(IDWriteTextLayout*& currentLayout, UnicodeString& text, UINT32 position, WCHAR const* textToInsert, UINT32 textToInsertLength, CaretFormat* caretFormat) {
        HRESULT hr = S_OK;

        // The inserted string gets all the properties of the character right before position.
        // If there is no text right before position, so use the properties of the character right after position.

        // Copy all the old formatting.
        if (currentLayout)
            currentLayout->AddRef();
        IDWriteTextLayout* oldLayout = currentLayout;
        UINT32 oldTextLength = text.Length;
        position = std::min(position, (uint32_t)text.Size);

        text.insert(position, textToInsert, textToInsertLength);

        hr = recreateLayout(currentLayout, text);

        IDWriteTextLayout* newLayout = currentLayout;

        if (SUCCEEDED(hr)) {
            copyGlobalProperties(oldLayout, newLayout);

            // For each property, get the position range and apply it to the old text.
            if (position == 0) {
                // Inserted text
                copySinglePropertyRange(oldLayout, 0, newLayout, 0, textToInsertLength);

                // The rest of the text
                copyRangedProperties(oldLayout, 0, oldTextLength, textToInsertLength, newLayout);
            } else {
                // 1st block
                copyRangedProperties(oldLayout, 0, position, 0, newLayout);

                // Inserted text
                copySinglePropertyRange(oldLayout, position - 1, newLayout, position, textToInsertLength, caretFormat);

                // Last block (if it exists)
                copyRangedProperties(oldLayout, position, oldTextLength, textToInsertLength, newLayout);
            }

            // Copy trailing end.
            copySinglePropertyRange(oldLayout, oldTextLength, newLayout, text.Length, UINT32_MAX);
        }

        if (oldLayout)
            oldLayout->Release();

        return S_OK;
    }
    
    HRESULT LayoutEditor::removeTextAt(IDWriteTextLayout*& currentLayout, UnicodeString& text, UINT32 position, UINT32 lengthToRemove) {
        // Removes text and shifts all formatting.

        HRESULT hr = S_OK;

        // copy all the old formatting.
        if (currentLayout)
            currentLayout->AddRef();
        IDWriteTextLayout* oldLayout = currentLayout;
        UINT32 oldTextLength = text.Length;

        text.remove(position, lengthToRemove);

        hr = recreateLayout(currentLayout, text);

        IDWriteTextLayout* newLayout = currentLayout;

        if (SUCCEEDED(hr)) {
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

        return S_OK;
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
