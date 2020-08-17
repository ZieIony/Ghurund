#pragma once

#include "Button.h"
#include "ui/control/Stack.h"
#include "ui/control/ImageView.h"
#include "ui/control/Border.h"
#include "ui/control/TextView.h"
#include "ui/control/Surface.h"
#include "ui/control/Clip.h"

namespace Ghurund::UI {
    class TextButton :public Button {
    private:
        TextView* text;

    public:
        TextButton(Font* font) {
            text = ghnew TextView(font);
            text->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
            Content = text;
        }

        TextButton(const String& text, Font* font):TextButton(font) {
            Text = text;
        }

        ~TextButton() {
            text->release();
        }

        const String& getText() const {
            return text->Text;
        }

        void setText(const String& text) {
            this->text->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const String& Text;

        inline unsigned int getTextColor() const {
            return text->TextColor;
        }

        inline void setTextColor(unsigned int color) {
            text->TextColor = color;
        }

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline Font* getFont() {
            return text->Font;
        }

        inline void setFont(Font* font) {
            text->Font = font;
        }

        __declspec(property(get = getFont, put = setFont)) Font* Font;

        virtual void measure() {
            text->PreferredSize = PreferredSize;
            __super::measure();
        }
    };
}