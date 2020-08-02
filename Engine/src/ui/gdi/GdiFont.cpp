#include "GdiFont.h"

namespace Ghurund {
    void GdiFont::measureText(const String& text, float width, Gdiplus::SizeF* outSize) const {
        HDC hdcimage = CreateCompatibleDC(NULL);
        Gdiplus::Graphics graphics(hdcimage);
        graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
        graphics.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
        Gdiplus::RectF rect(0, 0, width, MAX_SIZE);
        Gdiplus::RectF outRect;

        Gdiplus::StringFormat format;
        //format.SetTrimming(Gdiplus::StringTrimming::StringTrimmingCharacter);

        if (sizeof(tchar) == sizeof(char)) {
            graphics.MeasureString(UnicodeString(text), -1, font, rect, &format, &outRect);
        } else {
            graphics.MeasureString((UnicodeString&)text, -1, font, rect, &format, &outRect);
        }

        outSize->Width = outRect.GetRight();
        outSize->Height = outRect.GetBottom();
    }
}