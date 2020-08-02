#include "GdiCanvas.h"

namespace Ghurund {
    using namespace Gdiplus;

    void GdiCanvas::drawText(const String& text, float x, float y, float width, float height, const Ghurund::Font& font, const Paint& paint) {
        RectF rectF(x, y, width, height);

        color.SetValue(paint.Color);
        brush->SetColor(color);

        StringFormat format = {};
        format.SetLineAlignment(StringAlignmentCenter);
        //format.SetTrimming(Gdiplus::StringTrimming::StringTrimmingCharacter);

        if (sizeof(tchar) == sizeof(char)) {
            graphics->DrawString(UnicodeString(text), -1, ((GdiFont&)font).font, rectF, &format, brush);
        } else {
            graphics->DrawString((UnicodeString&)text, -1, ((GdiFont&)font).font, rectF, &format, brush);
        }
    }
}