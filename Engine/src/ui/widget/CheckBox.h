#pragma once

#include "ui/control/CheckableView.h"
#include "ui/control/ImageView.h"
#include "ui/control/TextView.h"
#include "ui/control/Row.h"
#include "ui/control/Space.h"

namespace Ghurund::UI {
    class CheckBoxRadioBase :public CheckableView {
    private:
        Row* row;
        TextView* textView;
        ImageView* imageView;
        Space* space;

    public:
        CheckBoxRadioBase() {
            row = ghnew Row();
            textView = ghnew TextView();
            imageView = ghnew ImageView();
            space = ghnew Space();
            row->Children.add({ imageView, space, textView });
            row->Gravity.vertical = Gravity::Vertical::CENTER;
            Child = row;

            Cursor = Cursor::HAND;
        }

        ~CheckBoxRadioBase() {
            row->release();
            textView->release();
            imageView->release();
            space->release();
        }

        const GdiImage* getImage() const {
            return imageView->Image;
        }

        void setImage(GdiImage* image) {
            imageView->Image = image;
        }

        __declspec(property(get = getImage, put = setImage)) GdiImage* Image;

        inline void setImageTint(unsigned int color) {
            imageView->Tint = color;
        }

        inline unsigned int getImageTint() {
            return imageView->Tint;
        }

        __declspec(property(get = getImageTint, put = setImageTint)) unsigned int ImageTint;

        const String& getText() const {
            return textView->Text;
        }

        void setText(const String& text) {
            textView->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const String& Text;

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

        virtual void measure() {
            row->PreferredSize = PreferredSize;
            __super::measure();
        }

        virtual void layout(float x, float y, float w, float h)override {
            __super::layout(x, y, w, h);
        }
    };

    class CheckBox :public CheckBoxRadioBase {
    public:
        CheckBox() {
            OnClicked.add([this](Control& sender, MouseButton button) {
                setChecked(!isChecked());
                });
        }
    };

    class RadioButton :public CheckBoxRadioBase {
    public:
        RadioButton() {
            OnClicked.add([this](Control& sender, MouseButton button) {
                setChecked(true);
                });
        }
    };
}