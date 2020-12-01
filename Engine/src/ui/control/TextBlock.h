#pragma once

#include "Control.h"
#include "ui/font/Font.h"
#include "ui/Style.h"
#include "ui/Graphics2D.h"

namespace Ghurund::UI {
    class TextBlock:public Control {
    private:
        Font* font = nullptr;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<TextBlock>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TextBlock))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    protected:
        UnicodeString text;
        Paint paint;
        IDWriteTextLayout* textLayout = nullptr;

        ~TextBlock() {
            if (font)
                font->release();
            if (textLayout)
                textLayout->Release();
        }

    public:
        TextBlock() {
            text = "text";
        }

        TextBlock(const UnicodeString& text, Font* font, uint32_t color = 0xde000000):text(text) {
            font->addReference();
            this->font = font;
            TextColor = color;
        }

        TextBlock(Style<TextBlock>* style) {
            style->apply(*this);
            style->onStateChanged(*this);
        }

        UnicodeString& getText() {
            return text;
        }

        void setText(const UnicodeString& text) {
            this->text = text;
        }

        __declspec(property(get = getText, put = setText)) UnicodeString& Text;

        inline unsigned int getTextColor() const {
            return paint.Color;
        }

        inline void setTextColor(unsigned int color) {
            paint.Color = color;
        }

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline Font* getFont() {
            return font;
        }

        inline void setFont(Font* font) {
            setPointer(this->font, font);
        }

        __declspec(property(get = getFont, put = setFont)) Font* Font;

        virtual void invalidate() override {
            if (textLayout) {
                textLayout->Release();
                textLayout = nullptr;
            }
            __super::invalidate();
        }

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}