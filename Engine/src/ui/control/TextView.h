#pragma once

#include "Control.h"
#include "ui/Font.h"

namespace Ghurund {
    class TextView :public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(TextView);

        String text;
        unsigned int textColor = 0xde000000;
        Font* font;

    public:

        TextView(Font *font):font(font) {}
        TextView(const String& text, Font* font):text(text), font(font) {}

        ~TextView() {
            delete font;
        }

        const String& getText() const {
            return text;
        }

        void setText(const String& text) {
            this->text = text;
        }

        __declspec(property(get = getText, put = setText)) const String& Text;

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

        virtual void measure();

        virtual void draw(Canvas& canvas)override;

        inline static const Ghurund::Type& TYPE = TypeBuilder<TextView>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(Control::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}