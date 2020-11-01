#pragma once

#include "Control.h"
#include "ui/gdi/GdiFont.h"
#include "ui/Style.h"

namespace Ghurund::UI {
    class TextBlock:public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(TextBlock);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<TextBlock>();

        String text;
        unsigned int textColor = 0xde000000;
        Font* font = nullptr;
        Paint paint;

    protected:
        ~TextBlock() {
            if (font)
                font->release();
        }

    public:
        TextBlock() {
            text = "text";
            cacheEnabled = true;
        }

        TextBlock(const String& text, Font* font):text(text) {
            font->addReference();
            this->font = font;
            cacheEnabled = true;
        }

        TextBlock(Style<TextBlock>* style):TextBlock() {
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

        inline static const Ghurund::Type& TYPE = TypeBuilder<TextBlock>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE());

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<TextBlock> TextBlockPtr;
}