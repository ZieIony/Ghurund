#pragma once

#include "ui/control/TextView.h"

namespace Ghurund::UI {
    class TextMixin {
    protected:
        TextView* textView = nullptr;

    public:
        const String& getText() const {
            return textView->Text;
        }

        void setText(const String& text) {
            this->textView->Text = text;
            this->textView->invalidateCache();
        }

        __declspec(property(get = getText, put = setText)) const String& Text;

        inline unsigned int getTextColor() const {
            return textView->TextColor;
        }

        inline void setTextColor(unsigned int color) {
            textView->TextColor = color;
            textView->invalidateCache();
        }

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline Font* getFont() {
            return textView->Font;
        }

        inline void setFont(Font* font) {
            textView->Font = font;
            textView->invalidateCache();
        }

        __declspec(property(get = getFont, put = setFont)) Font* Font;
    };

    class TextLayoutMixin {
    protected:
        TextView* textView;

    public:
        TextLayoutMixin() {
            textView = ghnew Ghurund::UI::TextView();
        }

        ~TextLayoutMixin() {
            textView->release();
        }

        inline TextView* getTextView() {
            return textView;
        }

        __declspec(property(get = getTextView)) TextView* TextView;
    };
}