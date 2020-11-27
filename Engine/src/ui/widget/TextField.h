#pragma once

#include "core/ScopedPointer.h"
#include "ui/Theme.h"
#include "ui/control/ClickableView.h"
#include "ui/control/TextBlock.h"

namespace Ghurund::UI {
    class TextField:public ClickableView {
    private:
        ScopedPointer<TextBlock> textView;
        Event<TextField> onTextChanged = Event<TextField>(*this);

    public:
        TextField() {
            textView = ghnew TextBlock();
            Child = textView;
        }

        TextField(Ghurund::UI::Theme& theme) {
            textView = ghnew TextBlock(theme.textViewPrimaryStyle);
            Child = textView;
        }

        UnicodeString& getText() {
            return textView->Text;
        }

        void setText(const UnicodeString& text) {
            textView->Text = text;
        }

        __declspec(property(get = getText, put = setText)) UnicodeString& Text;

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

        inline Event<TextField>& getOnTextChanged() {
            return onTextChanged;
        }

        __declspec(property(get = getOnTextChanged)) Event<TextField>& OnTextChanged;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override {
            if (event.Action == KeyAction::CHAR) {
                textView->Text.add((tchar)event.Key);
                onTextChanged();
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
            __super::dispatchMouseMotionEvent(event);
            return true;
        }
    };

    typedef ScopedPointer<TextField> TextFieldPtr;
}