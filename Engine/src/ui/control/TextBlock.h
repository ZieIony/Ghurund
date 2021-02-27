#pragma once

#include "Control.h"
#include "ui/Paint.h"
#include "ui/font/TextFormat.h"
#include "ui/style/Style.h"

struct IDWriteTextLayout;

namespace Ghurund::UI {
    class TextBlock:public Control {
    private:
        TextFormat* textFormat = nullptr;

    protected:
        WString text;
        uint32_t textColor = 0xdd000000;
        Paint paint;
        IDWriteTextLayout* textLayout = nullptr;

        ~TextBlock() {
            if (textFormat)
                textFormat->release();
            if (textLayout)
                textLayout->Release();
        }

        void makeLayout(float width, float height);

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        static const Ghurund::Type& GET_TYPE();

    public:
        TextBlock() {
            text = L"text";
        }

        TextBlock(const WString& text, TextFormat* textFormat, uint32_t color = 0xde000000) {
            textFormat->addReference();
            this->text = text;
            this->textFormat = textFormat;
            TextColor = color;
        }

        const WString& getText() {
            return text;
        }

        inline void setText(const WString& text) {
            if (this->text == text)
                return;
            this->text = text;
            if (textLayout) {
                textLayout->Release();
                textLayout = nullptr;
            }
        }

        __declspec(property(get = getText, put = setText)) const WString& Text;

        inline unsigned int getTextColor() const {
            return textColor;
        }

        inline void setTextColor(unsigned int color) {
            textColor = color;
        }

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline TextFormat* getFont() {
            return textFormat;
        }

        inline void setFont(TextFormat* textFormat) {
            if (this->textFormat == textFormat)
                return;
            setPointer(this->textFormat, textFormat);
            invalidate();
        }

        __declspec(property(get = getFont, put = setFont)) TextFormat* TextFormat;

        void dispatchContextChanged();

        virtual void invalidate() override {
            if (textLayout) {
                textLayout->Release();
                textLayout = nullptr;
            }
            __super::invalidate();
        }

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}