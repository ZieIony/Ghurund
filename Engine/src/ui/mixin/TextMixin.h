#pragma once

#include "ui/control/TextBlock.h"

namespace Ghurund::UI {
    class TextMixin {
    protected:
        TextBlock* textView = nullptr;

    public:
        const UnicodeString& getText() const {
            return textView->Text;
        }

        void setText(const UnicodeString& text) {
            this->textView->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const UnicodeString& Text;

        inline unsigned int getTextColor() const {
            return textView->TextColor;
        }

        inline void setTextColor(unsigned int color) {
            textView->TextColor = color;
        }

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline Font* getFont() {
            return textView->Font;
        }

        inline void setFont(Font* font) {
            textView->Font = font;
        }

        __declspec(property(get = getFont, put = setFont)) Font* Font;
    };

    class TextLayoutMixin {
    protected:
        TextBlock* textView;

    public:
        TextLayoutMixin() {
            textView = ghnew Ghurund::UI::TextBlock();
        }

        ~TextLayoutMixin() {
            textView->release();
        }

        inline TextBlock* getTextBlock() {
            return textView;
        }

        __declspec(property(get = getTextBlock)) TextBlock* TextBlock;
    };
}