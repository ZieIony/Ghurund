#include "TextView.h"

namespace Ghurund::UI {
    DWRITE_TEXT_RANGE TextView::getSelectionRange() {
        uint32_t caretBegin = caretAnchor;
        uint32_t caretEnd = caretPosition + caretPositionOffset;
        if (caretBegin > caretEnd)
            std::swap(caretBegin, caretEnd);

        caretBegin = std::min(caretBegin, (uint32_t)Text.Length);
        caretEnd = std::min(caretEnd, (uint32_t)Text.Length);

        DWRITE_TEXT_RANGE textRange = { caretBegin, caretEnd - caretBegin };
        return textRange;
    }

    D2D1_RECT_F TextView::getCaretRect() {
        if (!textLayout)
            return {};

        DWRITE_HIT_TEST_METRICS caretMetrics;
        float caretX, caretY;

        textLayout->HitTestTextPosition(caretPosition, caretPositionOffset > 0, &caretX, &caretY, &caretMetrics);

        DWRITE_TEXT_RANGE selectionRange = getSelectionRange();
        if (selectionRange.length > 0) {
            UINT32 actualHitTestCount = 1;
            textLayout->HitTestTextRange(caretPosition, 0, 0, 0, &caretMetrics, 1, &actualHitTestCount);

            caretY = caretMetrics.top;
        }

        DWORD caretIntThickness = 2;
        SystemParametersInfo(SPI_GETCARETWIDTH, 0, &caretIntThickness, FALSE);
        const float caretThickness = float(caretIntThickness);

        D2D1_RECT_F rect;
        rect.left = caretX - caretThickness / 2.0f;
        rect.right = rect.left + caretThickness;
        rect.top = caretY;
        rect.bottom = caretY + caretMetrics.height;
        return rect;
    }

    void TextView::getLineMetrics(std::vector<DWRITE_LINE_METRICS>& lineMetrics) {
        DWRITE_TEXT_METRICS textMetrics;
        textLayout->GetMetrics(&textMetrics);

        lineMetrics.resize(textMetrics.lineCount);
        textLayout->GetLineMetrics(&lineMetrics.front(), textMetrics.lineCount, &textMetrics.lineCount);
    }

    void TextView::getLineFromPosition(const DWRITE_LINE_METRICS* lineMetrics, UINT32 lineCount, UINT32 textPosition, UINT32* lineOut, UINT32* linePositionOut) {
        UINT32 line = 0;
        UINT32 linePosition = 0;
        UINT32 nextLinePosition = 0;
        for (; line < lineCount; ++line) {
            linePosition = nextLinePosition;
            nextLinePosition = linePosition + lineMetrics[line].length;
            if (nextLinePosition > textPosition)
                break;
        }
        *linePositionOut = linePosition;
        *lineOut = std::min(line, lineCount - 1);
        return;
    }

    void TextView::alignCaretToNearestCluster(bool isTrailingHit = false, bool skipZeroWidth = false) {
        DWRITE_HIT_TEST_METRICS hitTestMetrics;
        float caretX, caretY;

        textLayout->HitTestTextPosition(caretPosition, false, &caretX, &caretY, &hitTestMetrics);

        caretPosition = hitTestMetrics.textPosition;
        caretPositionOffset = (isTrailingHit) ? hitTestMetrics.length : 0;

        if (skipZeroWidth && hitTestMetrics.width == 0) {
            caretPosition += caretPositionOffset;
            caretPositionOffset = 0;
        }
    }

    void TextView::updateCaretFormatting() {
        UINT32 currentPos = caretPosition + caretPositionOffset;

        if (currentPos > 0) {
            --currentPos; // Always adopt the trailing properties.
        }

        // Get the family name
        caretFormat.fontFamilyName[0] = '\0';
        textLayout->GetFontFamilyName(currentPos, &caretFormat.fontFamilyName[0], ARRAYSIZE(caretFormat.fontFamilyName));

        // Get the locale
        caretFormat.localeName[0] = '\0';
        textLayout->GetLocaleName(currentPos, &caretFormat.localeName[0], ARRAYSIZE(caretFormat.localeName));

        // Get the remaining attributes...
        textLayout->GetFontWeight(currentPos, &caretFormat.fontWeight);
        textLayout->GetFontStyle(currentPos, &caretFormat.fontStyle);
        textLayout->GetFontStretch(currentPos, &caretFormat.fontStretch);
        textLayout->GetFontSize(currentPos, &caretFormat.fontSize);
        textLayout->GetUnderline(currentPos, &caretFormat.hasUnderline);
        textLayout->GetStrikethrough(currentPos, &caretFormat.hasStrikethrough);

        // Get the current color.
        IUnknown* drawingEffect = nullptr;
        textLayout->GetDrawingEffect(currentPos, &drawingEffect);
        caretFormat.color = 0;
        if (drawingEffect) {
            DrawingEffect& effect = *(DrawingEffect*)drawingEffect;
            caretFormat.color = effect.getColor();
            drawingEffect->Release();
        }
    }

    void TextView::updateSystemCaret(const D2D1_RECT_F& rect) {
        if (Focused)
            return;

        /*
        D2D1::Matrix3x2F pageTransform;
        GetViewMatrix(&Cast(pageTransform));

        // Transform caret top/left and size according to current scale and origin.
        D2D1_POINT_2F caretPoint = pageTransform.TransformPoint(D2D1::Point2F(rect.left, rect.top));

        float width = (rect.right - rect.left);
        float height = (rect.bottom - rect.top);
        float transformedWidth = width * pageTransform._11 + height * pageTransform._21;
        float transformedHeight = width * pageTransform._12 + height * pageTransform._22;

        // Update the caret's location, rounding to nearest integer so that
        // it lines up with the text selection.

        int intX = RoundToInt(caretPoint.x);
        int intY = RoundToInt(caretPoint.y);
        int intWidth = RoundToInt(transformedWidth);
        int intHeight = RoundToInt(caretPoint.y + transformedHeight) - intY;

        CreateCaret(Window->Handle, NULL, intWidth, intHeight);
        SetCaretPos(intX, intY);
        */
    }

    bool TextView::setSelectionFromPoint(float x, float y, bool extendSelection) {
        // Returns the text position corresponding to the mouse x,y.
        // If hitting the trailing side of a cluster, return the
        // leading edge of the following text position.

        BOOL isTrailingHit;
        BOOL isInside;
        DWRITE_HIT_TEST_METRICS caretMetrics;

        // Remap display coordinates to actual.
        DWRITE_MATRIX matrix;
        //GetInverseViewMatrix(&matrix);

        float transformedX = x;// (x * matrix.m11 + y * matrix.m21 + matrix.dx);
        float transformedY = y;// (x * matrix.m12 + y * matrix.m22 + matrix.dy);

        textLayout->HitTestPoint(transformedX, transformedY, &isTrailingHit, &isInside, &caretMetrics);

        // Update current selection according to click or mouse drag.
        setSelection(
            isTrailingHit ? SetSelectionModeAbsoluteTrailing : SetSelectionModeAbsoluteLeading,
            caretMetrics.textPosition,
            extendSelection
        );

        return true;
    }

    bool TextView::setSelection(SetSelectionMode moveMode, UINT32 advance, bool extendSelection, bool updateCaretFormat) {
        // Moves the caret relatively or absolutely, optionally extending the
        // selection range (for example, when shift is held).

        UINT32 line = UINT32_MAX; // current line number, needed by a few modes
        UINT32 absolutePosition = caretPosition + caretPositionOffset;
        UINT32 oldAbsolutePosition = absolutePosition;
        UINT32 oldCaretAnchor = caretAnchor;

        switch (moveMode) {
        case SetSelectionModeLeft:
            caretPosition += caretPositionOffset;
            if (caretPosition > 0) {
                --caretPosition;
                alignCaretToNearestCluster(false, true);

                // special check for CR/LF pair
                absolutePosition = caretPosition + caretPositionOffset;
                if (absolutePosition >= 1
                    && absolutePosition < text.Size
                    && text[absolutePosition - 1] == '\r'
                    && text[absolutePosition] == '\n') {
                    caretPosition = absolutePosition - 1;
                    alignCaretToNearestCluster(false, true);
                }
            }
            break;

        case SetSelectionModeRight:
            caretPosition = absolutePosition;
            alignCaretToNearestCluster(true, true);

            // special check for CR/LF pair
            absolutePosition = caretPosition + caretPositionOffset;
            if (absolutePosition >= 1
                && absolutePosition < text.Size
                && text[absolutePosition - 1] == '\r'
                && text[absolutePosition] == '\n') {
                caretPosition = absolutePosition + 1;
                alignCaretToNearestCluster(false, true);
            }
            break;

        case SetSelectionModeLeftChar:
            caretPosition = absolutePosition;
            caretPosition -= std::min(advance, absolutePosition);
            caretPositionOffset = 0;
            break;

        case SetSelectionModeRightChar:
            caretPosition = absolutePosition + advance;
            caretPositionOffset = 0;
            {
                // Use hit-testing to limit text position.
                DWRITE_HIT_TEST_METRICS hitTestMetrics;
                float caretX, caretY;

                textLayout->HitTestTextPosition(
                    caretPosition,
                    false,
                    &caretX,
                    &caretY,
                    &hitTestMetrics
                );
                caretPosition = std::min(caretPosition, hitTestMetrics.textPosition + hitTestMetrics.length);
            }
            break;

        case SetSelectionModeUp:
        case SetSelectionModeDown:
        {
            // Retrieve the line metrics to figure out what line we are on.
            std::vector<DWRITE_LINE_METRICS> lineMetrics;
            getLineMetrics(lineMetrics);

            UINT32 linePosition;
            getLineFromPosition(&lineMetrics.front(), static_cast<UINT32>(lineMetrics.size()), caretPosition, &line, &linePosition);

            // Move up a line or down
            if (moveMode == SetSelectionModeUp) {
                if (line <= 0)
                    break; // already top line
                line--;
                linePosition -= lineMetrics[line].length;
            } else {
                linePosition += lineMetrics[line].length;
                line++;
                if (line >= lineMetrics.size())
                    break; // already bottom line
            }

            // To move up or down, we need three hit-testing calls to determine:
            // 1. The x of where we currently are.
            // 2. The y of the new line.
            // 3. New text position from the determined x and y.
            // This is because the characters are variable size.

            DWRITE_HIT_TEST_METRICS hitTestMetrics;
            float caretX, caretY, dummyX;

            // Get x of current text position
            textLayout->HitTestTextPosition(
                caretPosition,
                caretPositionOffset > 0, // trailing if nonzero, else leading edge
                &caretX,
                &caretY,
                &hitTestMetrics
            );

            // Get y of new position
            textLayout->HitTestTextPosition(
                linePosition,
                false, // leading edge
                &dummyX,
                &caretY,
                &hitTestMetrics
            );

            // Now get text position of new x,y.
            BOOL isInside, isTrailingHit;
            textLayout->HitTestPoint(
                caretX,
                caretY,
                &isTrailingHit,
                &isInside,
                &hitTestMetrics
            );

            caretPosition = hitTestMetrics.textPosition;
            caretPositionOffset = isTrailingHit ? (hitTestMetrics.length > 0) : 0;
        }
        break;

        case SetSelectionModeLeftWord:
        case SetSelectionModeRightWord:
        {
            // To navigate by whole words, we look for the canWrapLineAfter
            // flag in the cluster metrics.

            // First need to know how many clusters there are.
            std::vector<DWRITE_CLUSTER_METRICS> clusterMetrics;
            UINT32 clusterCount;
            textLayout->GetClusterMetrics(NULL, 0, &clusterCount);

            if (clusterCount == 0)
                break;

            // Now we actually read them.
            clusterMetrics.resize(clusterCount);
            textLayout->GetClusterMetrics(&clusterMetrics.front(), clusterCount, &clusterCount);

            caretPosition = absolutePosition;

            UINT32 clusterPosition = 0;
            UINT32 oldCaretPosition = caretPosition;

            if (moveMode == SetSelectionModeLeftWord) {
                // Read through the clusters, keeping track of the farthest valid
                // stopping point just before the old position.
                caretPosition = 0;
                caretPositionOffset = 0; // leading edge
                for (UINT32 cluster = 0; cluster < clusterCount; ++cluster) {
                    clusterPosition += clusterMetrics[cluster].length;
                    if (clusterMetrics[cluster].canWrapLineAfter) {
                        if (clusterPosition >= oldCaretPosition)
                            break;

                        // Update in case we pass this point next loop.
                        caretPosition = clusterPosition;
                    }
                }
            } else // SetSelectionModeRightWord
            {
                // Read through the clusters, looking for the first stopping point
                // after the old position.
                for (UINT32 cluster = 0; cluster < clusterCount; ++cluster) {
                    UINT32 clusterLength = clusterMetrics[cluster].length;
                    caretPosition = clusterPosition;
                    caretPositionOffset = clusterLength; // trailing edge
                    if (clusterPosition >= oldCaretPosition && clusterMetrics[cluster].canWrapLineAfter)
                        break; // first stopping point after old position.

                    clusterPosition += clusterLength;
                }
            }
        }
        break;

        case SetSelectionModeHome:
        case SetSelectionModeEnd:
        {
            // Retrieve the line metrics to know first and last position
            // on the current line.
            std::vector<DWRITE_LINE_METRICS> lineMetrics;
            getLineMetrics(lineMetrics);

            getLineFromPosition(&lineMetrics.front(), static_cast<UINT32>(lineMetrics.size()), caretPosition, &line, &caretPosition);

            caretPositionOffset = 0;
            if (moveMode == SetSelectionModeEnd) {
                // Place the caret at the last character on the line,
                // excluding line breaks. In the case of wrapped lines,
                // newlineLength will be 0.
                UINT32 lineLength = lineMetrics[line].length - lineMetrics[line].newlineLength;
                caretPositionOffset = std::min(lineLength, 1u);
                caretPosition += lineLength - caretPositionOffset;
                alignCaretToNearestCluster(true);
            }
        }
        break;

        case SetSelectionModeFirst:
            caretPosition = 0;
            caretPositionOffset = 0;
            break;

        case SetSelectionModeAll:
            caretAnchor = 0;
            extendSelection = true;
            __fallthrough;

        case SetSelectionModeLast:
            caretPosition = UINT32_MAX;
            caretPositionOffset = 0;
            alignCaretToNearestCluster(true);
            break;

        case SetSelectionModeAbsoluteLeading:
            caretPosition = advance;
            caretPositionOffset = 0;
            break;

        case SetSelectionModeAbsoluteTrailing:
            caretPosition = advance;
            alignCaretToNearestCluster(true);
            break;
        }

        absolutePosition = caretPosition + caretPositionOffset;

        if (!extendSelection)
            caretAnchor = absolutePosition;

        bool caretMoved = (absolutePosition != oldAbsolutePosition) || (caretAnchor != oldCaretAnchor);

        if (caretMoved) {
            if (updateCaretFormat)
                updateCaretFormatting();

            repaint();

            auto rect = getCaretRect();
            updateSystemCaret(rect);
        }

        return caretMoved;
    }

    void TextView::onDraw(Canvas& canvas) {
        DWRITE_TEXT_RANGE caretRange = getSelectionRange();
        UINT32 actualHitTestCount = 0;

        if (caretRange.length > 0)
            textLayout->HitTestTextRange(caretRange.startPosition, caretRange.length, 0, 0, nullptr, 0, &actualHitTestCount);

        std::vector<DWRITE_HIT_TEST_METRICS> hitTestMetrics(actualHitTestCount);

        if (caretRange.length > 0)
            textLayout->HitTestTextRange(caretRange.startPosition, caretRange.length, 0, 0, &hitTestMetrics[0], hitTestMetrics.size(), &actualHitTestCount);

        if (actualHitTestCount > 0) {
            canvas.AntialiasingEnabled = false;

            for (size_t i = 0; i < actualHitTestCount; ++i) {
                const DWRITE_HIT_TEST_METRICS& htm = hitTestMetrics[i];
                paint.Color = textSelectionEffect->getColor();
                canvas.fillRect(htm.left, htm.top, htm.width, htm.height, paint);
            }

            canvas.AntialiasingEnabled = true;
        }

        if (Focused) {
            auto caretRect = getCaretRect();
            canvas.AntialiasingEnabled = false;
            paint.Color = caretBackgroundEffect->getColor();
            canvas.fillRect(caretRect, paint);
            canvas.AntialiasingEnabled = true;
        }

        paint.Color = TextColor;
        canvas.drawText(textLayout, 0, 0, paint);

        if (actualHitTestCount > 0) {
            canvas.AntialiasingEnabled = false;

            for (size_t i = 0; i < actualHitTestCount; ++i) {
                const DWRITE_HIT_TEST_METRICS& htm = hitTestMetrics[i];
                if (htm.isText)
                    continue; // Only draw selection if not text.

                paint.Color = imageSelectionEffect->getColor();
                canvas.fillRect(htm.left, htm.top, htm.width, htm.height, paint);
            }

            canvas.AntialiasingEnabled = true;
        }
    }
}
