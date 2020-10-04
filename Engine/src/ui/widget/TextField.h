#pragma once

#include "core/ScopedPointer.h"
#include "ui/control/ClickableView.h"
#include "ui/control/TextView.h"

namespace Ghurund::UI {
    class TextField:public ClickableView {
    private:
        ScopedPointer<TextView> textView;

    public:
        TextField() {
            textView = ghnew TextView();
            Child = textView;
        }

        TextField(Theme& theme) {
            textView = ghnew TextView(theme.textViewPrimaryStyle);
            Child = textView;
        }

        String& getText() {
            return textView->Text;
        }

        void setText(const String& text) {
            textView->Text = text;
        }

        __declspec(property(get = getText, put = setText)) String& Text;

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

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override {
            if (event.Action == KeyAction::CHAR) {
                textView->Text.add((tchar)event.Key);
                textView->invalidate();
                textView->repaint();
            }
            return true;
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            if (event.Action == MouseAction::DOWN)
                requestFocus();
            return __super::dispatchMouseButtonEvent(event);
        }


        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            if (Hovered || Pressed)
                Cursor::IBEAM.set();
            return true | __super::dispatchMouseMotionEvent(event);
        }
    };
}