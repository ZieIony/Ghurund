#include "TextView.h"

namespace Ghurund {
    void TextView::measure() {
        if (desiredSize.x == LayoutSize::WRAP_CONTENT) {
            Gdiplus::SizeF outSize;
            font->measureText(text, MAX_SIZE, &outSize);
            measuredSize.x = std::max(minSize.x, outSize.Width);
        } else if (desiredSize.x == LayoutSize::MATCH_PARENT) {
            measuredSize.x = MAX_SIZE;
        } else {
            measuredSize.x = desiredSize.x;
        }

        if (desiredSize.y == LayoutSize::WRAP_CONTENT) {
            Gdiplus::SizeF outSize;
            font->measureText(text, measuredSize.x, &outSize);
            measuredSize.y = std::max(minSize.y, outSize.Height);
        } else if (desiredSize.y == LayoutSize::MATCH_PARENT) {
            measuredSize.y = MAX_SIZE;
        } else {
            measuredSize.y = desiredSize.y;
        }
    }
    
    void TextView::draw(Canvas& canvas) {
        paint.Color = textColor;
        canvas.drawText(Text, position.x, position.y, size.x, size.y, *font, paint);
    }
}