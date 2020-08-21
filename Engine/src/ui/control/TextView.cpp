#include "TextView.h"

namespace Ghurund::UI {
    void TextView::measure() {
        float MAX_SIZE = 32768.0f;

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            Gdiplus::SizeF outSize;
            if (font)
                font->measureText(text, MAX_SIZE, &outSize);
            measuredSize.x = std::max(minSize.x, outSize.Width);
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.x = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            Gdiplus::SizeF outSize;
            if (font)
                font->measureText(text, (float)measuredSize.x, &outSize);
            measuredSize.y = std::max(minSize.y, outSize.Height);
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.y = (float)preferredSize.height;
        }
    }

    void TextView::draw(Canvas& canvas) {
        if (font) {
            paint.Color = textColor;
            canvas.drawText(Text, 0, 0, size.x, size.y, *font, paint);
        }
    }

    TextView* TextView::inflate(LayoutInflater& inflater, json& json) {
        TextView* textView = ghnew TextView();
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