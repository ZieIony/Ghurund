#include "TextView.h"

#include "application/Clipboard.h"
#include "ui/Cursor.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    TextView::~TextView() {
        if (textSelectionEffect)
            textSelectionEffect->Release();
        if (imageSelectionEffect)
            imageSelectionEffect->Release();
        if (caretBackgroundEffect)
            caretBackgroundEffect->Release();
    }

    DWRITE_TEXT_RANGE TextView::getSelectionRange() {
        uint32_t caretBegin = caretAnchor;
        uint32_t caretEnd = caretPosition + caretPositionOffset;
        if (caretBegin > caretEnd)
            std::swap(caretBegin, caretEnd);

        caretBegin = std::min(caretBegin, (uint32_t)Text.Length);
        caretEnd = std::min(caretEnd, (uint32_t)Text.Length);

        return { caretBegin, caretEnd - caretBegin };
    }

    D2D1_RECT_F TextView::getCaretRect() {
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

        D2D1_RECT_F rect = {
            caretX - caretThickness / 2.0f,
            caretY,
            caretX + caretThickness / 2.0f,
            caretY + caretMetrics.height,
        };
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

        if (currentPos > 0)
            currentPos--;

        if (currentFont)
            currentFont->release();

        if (textLayout) {
            currentFont = ghnew Ghurund::UI::TextFormat(textLayout, currentPos);

            IUnknown* drawingEffect = nullptr;
            textLayout->GetDrawingEffect(currentPos, &drawingEffect);
            if (drawingEffect) {
                DrawingEffect& effect = *(DrawingEffect*)drawingEffect;
                currentColor = effect.Color;
                drawingEffect->Release();
            } else {
                currentColor = 0;
            }
        } else if (TextFormat) {
            TextFormat->addReference();
            currentFont = TextFormat;
        }
    }

    void TextView::updateSystemCaret(const D2D1_RECT_F& rect) {
        if (Focused || !Context)
            return;

        CreateCaret(Context->Window.Handle, NULL, (int)(rect.right - rect.left), (int)(rect.bottom - rect.top));
        SetCaretPos((int)(rect.left), (int)(rect.top));
    }

    bool TextView::setSelectionFromPoint(float x, float y, bool extendSelection) {
        BOOL isTrailingHit;
        BOOL isInside;
        DWRITE_HIT_TEST_METRICS caretMetrics;

        textLayout->HitTestPoint(x, y, &isTrailingHit, &isInside, &caretMetrics);

        setSelection(
            isTrailingHit ? SetSelectionMode::AbsoluteTrailing : SetSelectionMode::AbsoluteLeading,
            caretMetrics.textPosition,
            extendSelection
        );

        return true;
    }

    bool TextView::setSelection(SetSelectionMode moveMode, UINT32 advance, bool extendSelection, bool updateCaretFormat) {
        UINT32 line = UINT32_MAX;
        UINT32 absolutePosition = caretPosition + caretPositionOffset;
        UINT32 oldAbsolutePosition = absolutePosition;
        UINT32 oldCaretAnchor = caretAnchor;

        switch (moveMode) {
        case SetSelectionMode::Left:
            caretPosition += caretPositionOffset;
            if (caretPosition > 0) {
                caretPosition--;
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

        case SetSelectionMode::Right:
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

        case SetSelectionMode::LeftChar:
            caretPosition = absolutePosition;
            caretPosition -= std::min(advance, absolutePosition);
            caretPositionOffset = 0;
            break;

        case SetSelectionMode::RightChar:
            caretPosition = absolutePosition + advance;
            caretPositionOffset = 0;
            {
                // Use hit-testing to limit text position.
                DWRITE_HIT_TEST_METRICS hitTestMetrics;
                float caretX, caretY;

                textLayout->HitTestTextPosition(caretPosition, false, &caretX, &caretY, &hitTestMetrics);
                caretPosition = std::min(caretPosition, hitTestMetrics.textPosition + hitTestMetrics.length);
            }
            break;

        case SetSelectionMode::Up:
        case SetSelectionMode::Down:
        {
            // Retrieve the line metrics to figure out what line we are on.
            std::vector<DWRITE_LINE_METRICS> lineMetrics;
            getLineMetrics(lineMetrics);

            UINT32 linePosition;
            getLineFromPosition(&lineMetrics.front(), static_cast<UINT32>(lineMetrics.size()), caretPosition, &line, &linePosition);

            // Move up a line or down
            if (moveMode == SetSelectionMode::Up) {
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
            textLayout->HitTestTextPosition(caretPosition, caretPositionOffset > 0, &caretX, &caretY, &hitTestMetrics);

            // Get y of new position
            textLayout->HitTestTextPosition(linePosition, false, &dummyX, &caretY, &hitTestMetrics);

            // Now get text position of new x,y.
            BOOL isInside, isTrailingHit;
            textLayout->HitTestPoint(caretX, caretY, &isTrailingHit, &isInside, &hitTestMetrics);

            caretPosition = hitTestMetrics.textPosition;
            caretPositionOffset = isTrailingHit ? (hitTestMetrics.length > 0) : 0;
        }
        break;

        case SetSelectionMode::LeftWord:
        case SetSelectionMode::RightWord:
        {
            // To navigate by whole words, we look for the canWrapLineAfter
            // flag in the cluster metrics.

            // First need to know how many clusters there are.
            std::vector<DWRITE_CLUSTER_METRICS> clusterMetrics;
            UINT32 clusterCount;
            textLayout->GetClusterMetrics(nullptr, 0, &clusterCount);

            if (clusterCount == 0)
                break;

            // Now we actually read them.
            clusterMetrics.resize(clusterCount);
            textLayout->GetClusterMetrics(&clusterMetrics.front(), clusterCount, &clusterCount);

            caretPosition = absolutePosition;

            UINT32 clusterPosition = 0;
            UINT32 oldCaretPosition = caretPosition;

            if (moveMode == SetSelectionMode::LeftWord) {
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
            } else {
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

        case SetSelectionMode::Home:
        case SetSelectionMode::End:
        {
            // Retrieve the line metrics to know first and last position
            // on the current line.
            std::vector<DWRITE_LINE_METRICS> lineMetrics;
            getLineMetrics(lineMetrics);

            getLineFromPosition(&lineMetrics.front(), static_cast<UINT32>(lineMetrics.size()), caretPosition, &line, &caretPosition);

            caretPositionOffset = 0;
            if (moveMode == SetSelectionMode::End) {
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

        case SetSelectionMode::First:
            caretPosition = 0;
            caretPositionOffset = 0;
            break;

        case SetSelectionMode::All:
            caretAnchor = 0;
            extendSelection = true;
            caretPosition = UINT32_MAX;
            caretPositionOffset = 0;
            alignCaretToNearestCluster(true);
            break;

        case SetSelectionMode::Last:
            caretPosition = UINT32_MAX;
            caretPositionOffset = 0;
            alignCaretToNearestCluster(true);
            break;

        case SetSelectionMode::AbsoluteLeading:
            caretPosition = advance;
            caretPositionOffset = 0;
            break;

        case SetSelectionMode::AbsoluteTrailing:
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

    void TextView::copyToClipboard() {
        DWRITE_TEXT_RANGE selectionRange = getSelectionRange();
        if (selectionRange.length <= 0 || !Context)
            return;

        Clipboard::putUnicodeText(Context->Window.Handle, Text.substring(selectionRange.startPosition, selectionRange.length));
    }

    void TextView::onThemeChanged() {
        if (!Theme)
            return;
        textSelectionEffect = ghnew DrawingEffect(Theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND]);
        imageSelectionEffect = ghnew DrawingEffect(Theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND]);
        caretBackgroundEffect = ghnew DrawingEffect(Theme->Colors[Theme::COLOR_PRIMARY_ONBACKGROUND]);
        if (!cursorDrawable)
            CursorDrawable = ghnew Ghurund::UI::CursorDrawable();
        updateCaretFormatting();
    }

    bool TextView::dispatchKeyEvent(const KeyEventArgs& event) {
        if (event.Action == KeyAction::DOWN && event.Key == 'C' && Context->Window.Input.isControlDown()) {
            copyToClipboard();
            return true;
        }
        return __super::dispatchKeyEvent(event);
    }

    bool TextView::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (event.Button == MouseButton::LEFT) {
            if (event.Action == MouseAction::DOWN) {
                pressed = true;
                setSelectionFromPoint((float)event.Position.x, (float)event.Position.y, Context->Window.Input.isShiftDown());
                Parent->CapturedChild = this;
            } else {
                pressed = false;
                Parent->CapturedChild = nullptr;
            }
        }
        return __super::dispatchMouseButtonEvent(event);
    }

    bool TextView::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (pressed)
            setSelectionFromPoint((float)event.Position.x, (float)event.Position.y, true);

        return __super::dispatchMouseMotionEvent(event);
    }

    void TextView::onDraw(Canvas& canvas) {
        if (Enabled) {
            DWRITE_TEXT_RANGE caretRange = getSelectionRange();
            UINT32 actualHitTestCount = 0;

            if (caretRange.length > 0)
                textLayout->HitTestTextRange(caretRange.startPosition, caretRange.length, 0, 0, nullptr, 0, &actualHitTestCount);

            Array<DWRITE_HIT_TEST_METRICS> hitTestMetrics(actualHitTestCount);

            if (caretRange.length > 0)
                textLayout->HitTestTextRange(caretRange.startPosition, caretRange.length, 0, 0, hitTestMetrics.begin(), (UINT32)hitTestMetrics.Size, &actualHitTestCount);

            if (actualHitTestCount > 0) {
                canvas.AntialiasingEnabled = false;

                for (const DWRITE_HIT_TEST_METRICS& htm : hitTestMetrics) {
                    paint.Color = textSelectionEffect->getColor();
                    canvas.fillRect(htm.left, htm.top, htm.width, htm.height, paint);
                }

                canvas.AntialiasingEnabled = true;
            }

            if (Focused) {
                canvas.AntialiasingEnabled = false;
                auto caretRect = getCaretRect();
                cursorDrawable->Color = caretBackgroundEffect->Color;
                cursorDrawable->Position = { caretRect.left, caretRect.top };
                cursorDrawable->Size = { caretRect.right - caretRect.left, caretRect.bottom - caretRect.top };
                cursorDrawable->draw(canvas);
                canvas.AntialiasingEnabled = true;
            }
        }

        paint.Color = TextColor;
        canvas.drawText(textLayout, 0, 0, paint);
    }
    
    const Ghurund::Type& TextView::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<TextView>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TextView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    
    TextView::TextView() {
        Cursor = &Cursor::IBEAM;
    }
}
