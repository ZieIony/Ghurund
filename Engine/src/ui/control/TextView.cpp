#include "TextView.h"

namespace Ghurund::UI {
    void TextView::measure() {
        float MAX_SIZE = 32768.0f;

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            Gdiplus::SizeF outSize;
            font->measureText(text, MAX_SIZE, &outSize);
            measuredSize.x = std::max(minSize.x, outSize.Width);
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.x = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            Gdiplus::SizeF outSize;
            font->measureText(text, (float)measuredSize.x, &outSize);
            measuredSize.y = std::max(minSize.y, outSize.Height);
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.y = (float)preferredSize.height;
        }
    }

    void TextView::draw(Canvas& canvas) {
        float lineHeight = font->getLineHeight();
        float padding = (size.y - lineHeight) / 2.0f;
        paint.Color = textColor;
        canvas.drawText2(Text, 0 ,0, size.x, size.y, *font, paint);

        /*float ascent = font->getAscent();
        float descent = font->getDescent();

        paint.Color = 0xffff0000;
        canvas.drawRect(0, 0, size.x, size.y, paint);
        paint.Color = 0xff00ff00;
        canvas.drawRect(30, 0, 200, ascent, paint);
        paint.Color = 0xff0000ff;
        canvas.drawRect(60, 0, 200, ascent + descent, paint);*/
    }

    TextView* TextView::inflate(LayoutInflater& inflater, json& json) {
        Ghurund::UI::Font* font = ghnew Ghurund::UI::Font("Arial", 10);
        TextView* textView = ghnew TextView(font);
        if (json.contains("text")) {
            nlohmann::json text = json["text"];
            if (text.is_string()) {
                std::string textString = text;
                textView->Text = textString.c_str();
            }
        }
        inflater.loadControl(textView, json);
        return textView;
    }
}