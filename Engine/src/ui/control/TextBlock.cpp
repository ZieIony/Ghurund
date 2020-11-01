#include "TextBlock.h"

namespace Ghurund::UI {
    void TextBlock::onMeasure(float parentWidth, float parentHeight) {
        if (preferredSize.width == PreferredSize::Width::WRAP) {
            Gdiplus::SizeF outSize;
            if (font) {
                font->measureText(text, parentWidth, &outSize);
            } else {
                Logger::log(LogType::WARNING, "TextBlock ({}) was not measured, because its font is null\n", text);
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

    void TextBlock::onDraw(Canvas& canvas) {
        if (font) {
            paint.Color = textColor;
            font->drawText(canvas, text, 0, 0, paint.Color);
        }
    }
}