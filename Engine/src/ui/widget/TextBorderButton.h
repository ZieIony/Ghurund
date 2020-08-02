#pragma once

#include "ui/control/Stack.h"
#include "ui/control/ImageView.h"
#include "ui/control/Border.h"
#include "ui/control/TextView.h"
#include "ui/control/Button.h"

namespace Ghurund {
    struct ButtonStyle {
        unsigned int borderColor, textColor;
        Drawable* backgroundDrawable = nullptr;
        Font* font = nullptr;

        ButtonStyle(unsigned int borderColor, unsigned int textColor, Font* font, Drawable* backgroundDrawable):
            borderColor(borderColor), textColor(textColor), font(font), backgroundDrawable(backgroundDrawable) {}

        ~ButtonStyle() {
            backgroundDrawable->release();
            font->release();
        }
    };

    class TextBorderButton :public Button {
    private:
        Border* border;
        DrawableView* background;
        TextView* text;
        Stack* stack;

    public:
        void setStyle(ButtonStyle& style) {
            BorderColor = style.borderColor;
            if (style.backgroundDrawable) {
                BackgroundDrawable = style.backgroundDrawable->clone();
            } else {
                BackgroundDrawable = nullptr;
            }
            text->TextColor = style.textColor;
        }

        inline unsigned int getBorderColor() const {
            return border->Color;
        }

        inline void setBorderColor(unsigned int color) {
            border->Color = color;
        }

        __declspec(property(get = getBorderColor, put = setBorderColor)) unsigned int BorderColor;

        void setBackgroundDrawable(Drawable* drawable) {
            background->Drawable = drawable;
        }

        Drawable* getBackgroundDrawable() {
            return background->Drawable;
        }

        __declspec(property(get = getBackgroundDrawable, put = setBackgroundDrawable)) Drawable* BackgroundDrawable;

        const String& getText() const {
            return text->Text;
        }

        void setText(const String& text) {
            this->text->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const String& Text;

        TextBorderButton(ButtonStyle& style) {
            border = ghnew Border(0x61000000);
            border->DesiredSize = XMFLOAT2(LayoutSize::MATCH_PARENT, LayoutSize::MATCH_PARENT);

            background = ghnew DrawableView(ghnew ColorDrawable(0x1f000000));
            background->DesiredSize = XMFLOAT2(LayoutSize::MATCH_PARENT, LayoutSize::MATCH_PARENT);

            text = ghnew TextView(style.font);
            text->DesiredSize = XMFLOAT2(LayoutSize::WRAP_CONTENT, LayoutSize::WRAP_CONTENT);

            stack = ghnew Stack();
            stack->Gravity = { HorizontalGravity::CENTER, VerticalGravity::CENTER };
            stack->Children.add({ border, background, text });
            Content = stack;
        }

        TextBorderButton(const String& text, ButtonStyle& style):TextBorderButton(style) {
            Text = text;
        }

        ~TextBorderButton() {
            stack->release();
            border->release();
            background->release();
            text->release();
        }

        virtual void measure() {
            text->DesiredSize = DesiredSize;
            __super::measure();
        }
    };
}