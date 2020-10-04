#pragma once

#include "Control.h"
#include "ui/gdi/GdiFont.h"
#include "ui/Style.h"

namespace Ghurund::UI {
    class TextView:public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(TextView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<TextView>();

        String text;
        unsigned int textColor = 0xde000000;
        Font* font = nullptr;
        Paint paint;
        bool pressed = false;
        TextSelection selectionStart, selectionEnd;
        unsigned int selectionColor = 0x7f0078D7;
        unsigned int cursorColor = 0xff333333;
        unsigned int cursorWidth = 2;

    protected:
        ~TextView() {
            if (font)
                font->release();
        }

    public:
        TextView() {
            text = "text";
            cacheEnabled = true;
        }

        TextView(const String& text, Font* font):text(text) {
            font->addReference();
            this->font = font;
            cacheEnabled = true;
        }

        TextView(Style<TextView>* style):TextView() {
            style->apply(*this);
            style->onStateChanged(*this);
        }

        String& getText() {
            return text;
        }

        void setText(const String& text) {
            this->text = text;
        }

        __declspec(property(get = getText, put = setText)) String& Text;

        inline unsigned int getTextColor() const {
            return textColor;
        }

        inline void setTextColor(unsigned int color) {
            textColor = color;
        }

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline Font* getFont() {
            return font;
        }

        inline void setFont(Font* font) {
            setPointer(this->font, font);
        }

        __declspec(property(get = getFont, put = setFont)) Font* Font;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        inline static const Ghurund::Type& TYPE = TypeBuilder<TextView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<TextView> TextViewPtr;
}