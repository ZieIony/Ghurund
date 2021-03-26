#include "ghuipch.h"
#include "TextView.h"

#include "core/window/Clipboard.h"
#include "ui/Cursor.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    Selection TextView::getSelectionRange() {
        uint32_t caretBegin = caretAnchor;
        uint32_t caretEnd = caretPosition + caretPositionOffset;
        if (caretBegin > caretEnd)
            std::swap(caretBegin, caretEnd);

        caretBegin = std::min(caretBegin, (uint32_t)Text.Length);
        caretEnd = std::min(caretEnd, (uint32_t)Text.Length);

        return { caretBegin, caretEnd - caretBegin };
    }

    FloatRect TextView::getCaretRect() {
        float caretX, caretY;
        HitTestMetrics caretMetrics = textLayout.hitTestTextPosition(caretPosition, caretPositionOffset > 0, &caretX, &caretY);

        Selection selectionRange = getSelectionRange();
        if (selectionRange.length > 0) {
            UINT32 actualHitTestCount = 1;
            Array<HitTestMetrics> metrics = textLayout.hitTestTextRange(caretPosition, 0, 0, 0);
            caretMetrics = metrics[0];

            caretY = caretMetrics.top;
        }

        DWORD caretIntThickness = 2;
        SystemParametersInfo(SPI_GETCARETWIDTH, 0, &caretIntThickness, FALSE);
        const float caretThickness = float(caretIntThickness);

        FloatRect rect = {
            caretX - caretThickness / 2.0f,
            caretY,
            caretX + caretThickness / 2.0f,
            caretY + caretMetrics.height,
        };
        return rect;
    }

    void TextView::getLineFromPosition(const LineMetrics* lineMetrics, UINT32 lineCount, UINT32 textPosition, UINT32* lineOut, UINT32* linePositionOut) {
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
        float caretX, caretY;

        HitTestMetrics hitTestMetrics = textLayout.hitTestTextPosition(caretPosition, false, &caretX, &caretY);

        caretPosition = hitTestMetrics.textPosition;
        caretPositionOffset = (isTrailingHit) ? hitTestMetrics.length : 0;

        if (skipZeroWidth && hitTestMetrics.width == 0) {
            caretPosition += caretPositionOffset;
            caretPositionOffset = 0;
        }
    }

    void TextView::updateSystemCaret(const FloatRect& rect) {
        if (Focused || !Context)
            return;

        CreateCaret(Context->Window.Handle, NULL, (int)(rect.right - rect.left), (int)(rect.bottom - rect.top));
        SetCaretPos((int)(rect.left), (int)(rect.top));
    }

    bool TextView::setSelectionFromPoint(float x, float y, bool extendSelection) {
        bool isTrailingHit;
        HitTestMetrics caretMetrics = textLayout.hitTestPoint(x, y, &isTrailingHit);

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
                    && absolutePosition < Text.Size
                    && Text[absolutePosition - 1] == '\r'
                    && Text[absolutePosition] == '\n') {
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
                && absolutePosition < Text.Size
                && Text[absolutePosition - 1] == '\r'
                && Text[absolutePosition] == '\n') {
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
                float caretX, caretY;

                HitTestMetrics hitTestMetrics = textLayout.hitTestTextPosition(caretPosition, false, &caretX, &caretY);
                caretPosition = std::min(caretPosition, hitTestMetrics.textPosition + hitTestMetrics.length);
            }
            break;

        case SetSelectionMode::Up:
        case SetSelectionMode::Down:
        {
            // Retrieve the line metrics to figure out what line we are on.
            Array<LineMetrics> lineMetrics = textLayout.getLineMetrics();

            UINT32 linePosition;
            getLineFromPosition(lineMetrics.begin(), static_cast<UINT32>(lineMetrics.Size), caretPosition, &line, &linePosition);

            // Move up a line or down
            if (moveMode == SetSelectionMode::Up) {
                if (line <= 0)
                    break; // already top line
                line--;
                linePosition -= lineMetrics[line].length;
            } else {
                linePosition += lineMetrics[line].length;
                line++;
                if (line >= lineMetrics.Size)
                    break; // already bottom line
            }

            // To move up or down, we need three hit-testing calls to determine:
            // 1. The x of where we currently are.
            // 2. The y of the new line.
            // 3. New text position from the determined x and y.
            // This is because the characters are variable size.

            float caretX, caretY, dummyX;

            // Get x of current text position
            textLayout.hitTestTextPosition(caretPosition, caretPositionOffset > 0, &caretX, &caretY);

            // Get y of new position
            textLayout.hitTestTextPosition(linePosition, false, &dummyX, &caretY);

            // Now get text position of new x,y.
            bool isTrailingHit;
            HitTestMetrics hitTestMetrics = textLayout.hitTestPoint(caretX, caretY, &isTrailingHit);

            caretPosition = hitTestMetrics.textPosition;
            caretPositionOffset = isTrailingHit ? (hitTestMetrics.length > 0) : 0;
        }
        break;

        case SetSelectionMode::LeftWord:
        case SetSelectionMode::RightWord:
        {
            // To navigate by whole words, we look for the canWrapLineAfter
            // flag in the cluster metrics.

            Array<ClusterMetrics> clusterMetrics = textLayout.ClusterMetrics;

            if (clusterMetrics.Empty)
                break;

            caretPosition = absolutePosition;

            UINT32 clusterPosition = 0;
            UINT32 oldCaretPosition = caretPosition;

            if (moveMode == SetSelectionMode::LeftWord) {
                // Read through the clusters, keeping track of the farthest valid
                // stopping point just before the old position.
                caretPosition = 0;
                caretPositionOffset = 0; // leading edge
                for (UINT32 cluster = 0; cluster < clusterMetrics.Size; ++cluster) {
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
                for (UINT32 cluster = 0; cluster < clusterMetrics.Size; ++cluster) {
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
            Array<LineMetrics> lineMetrics = textLayout.getLineMetrics();

            getLineFromPosition(lineMetrics.begin(), static_cast<UINT32>(lineMetrics.Size), caretPosition, &line, &caretPosition);

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
            repaint();

            auto rect = getCaretRect();
            updateSystemCaret(rect);
        }

        return caretMoved;
    }

    void TextView::copyToClipboard() {
        Selection selectionRange = getSelectionRange();
        if (selectionRange.length <= 0 || !Context)
            return;

        Clipboard::putUnicodeText(Context->Window.Handle, Text.substring(selectionRange.start, selectionRange.length));
    }

    void TextView::onThemeChanged() {
        if (!Theme)
            return;
        textSelectionEffect = Theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND];
        imageSelectionEffect = Theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND];
        caretBackgroundEffect = Theme->Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
        if (!cursorDrawable)
            CursorDrawable = ghnew Ghurund::UI::CursorDrawable();
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
            Selection caretRange = getSelectionRange();

            if (caretRange.length > 0) {
                Array<HitTestMetrics> hitTestMetrics = textLayout.hitTestTextRange(caretRange.start, caretRange.length, 0, 0);

                if (hitTestMetrics.Size > 0) {
                    canvas.AntialiasingEnabled = false;

                    for (const HitTestMetrics& htm : hitTestMetrics)
                        canvas.fillRect(htm.left, htm.top, htm.width, htm.height, textSelectionEffect);

                    canvas.AntialiasingEnabled = true;
                }
            }

            if (Focused) {
                canvas.AntialiasingEnabled = false;
                auto caretRect = getCaretRect();
                cursorDrawable->Color = caretBackgroundEffect;
                cursorDrawable->Size = { caretRect.right - caretRect.left, caretRect.bottom - caretRect.top };
                canvas.save();
                canvas.translate(caretRect.left, caretRect.top);
                cursorDrawable->draw(canvas);
                canvas.restore();
                canvas.AntialiasingEnabled = true;
            }
        }

        textLayout.draw(canvas, 0, 0);
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
