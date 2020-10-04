#include "TextView.h"

namespace Ghurund::UI {
    void TextView::onMeasure(float parentWidth, float parentHeight) {
        if (preferredSize.width == PreferredSize::Width::WRAP) {
            Gdiplus::SizeF outSize;
            if (font) {
                font->measureText(text, parentWidth, &outSize);
            } else {
                Logger::log(LogType::WARNING, "TextView ({}) was not measured, because its font is null\n", text);
            }
            measuredSize.width = std::max(minSize.width, outSize.Width);
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            Gdiplus::SizeF outSize;
            if (font)
                font->measureText(text, (float)measuredSize.width, &outSize);
            measuredSize.height = std::max(minSize.height, outSize.Height);
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
        }
    }

    void TextView::onDraw(Canvas& canvas) {
        if (font) {
            if (selectionStart.index != selectionEnd.index) {
                paint.Color = selectionColor;
                canvas.fillRect(std::min(selectionStart.x, selectionEnd.x), 0, std::abs(selectionStart.x - selectionEnd.x), size.height, paint);
            }
            paint.Color = cursorColor;
            canvas.fillRect(selectionEnd.x - cursorWidth / 2, 0, cursorWidth, size.height, paint);
            paint.Color = textColor;
            font->drawText(canvas, text, 0, 0, paint.Color);
        }
    }

    bool TextView::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (event.Action == MouseAction::DOWN) {
            pressed = true;
            if (font) {
                selectionStart = selectionEnd = font->findSelection(text, event.Position.x);
                repaint();
                return true;
            }
        } else {
            pressed = false;
            if (font) {
                selectionEnd = font->findSelection(text, event.Position.x);
                repaint();
                return true;
            }
        }
        return __super::dispatchMouseButtonEvent(event);
    }

    bool TextView::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (pressed) {
            if (font) {
                selectionEnd = font->findSelection(text, event.Position.x);
                repaint();
                return true;
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }
}