#pragma once

#include "ui/control/TextBlock.h"

namespace Ghurund::UI {
    class TextMixin {
    protected:
        TextBlock* textView = nullptr;

    public:
        const WString& getText() const {
            return textView->Text;
        }

        void setText(const WString& text) {
            this->textView->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const WString& Text;

        inline unsigned int getTextColor() const {
            return textView->TextColor;
        }

        inline void setTextColor(unsigned int color) {
            textView->TextColor = color;
        }

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline TextFormat* getFont() {
            return textView->TextFormat;
        }

        inline void setFont(TextFormat* textFormat) {
            textView->TextFormat = textFormat;
        }

        __declspec(property(get = getFont, put = setFont)) TextFormat* TextFormat;
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