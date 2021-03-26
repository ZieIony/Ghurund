#pragma once

#include "TextFormat.h"
#include "TextLayout.h"
#include "ui/Color.h"
#include "ui/control/Control.h"
#include "ui/style/Style.h"

struct IDWriteTextLayout;

namespace Ghurund::UI {
    class TextBlock:public Control {
    protected:
        TextLayout textLayout;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        static const Ghurund::Type& GET_TYPE();

    public:
        TextBlock():textLayout(L"text", 0xdd000000, nullptr) {}

        TextBlock(const WString& text, uint32_t color = 0xde000000, TextFormat* textFormat = nullptr):textLayout(text, color, textFormat) {}

        const WString& getText() {
            return textLayout.Text;
        }

        inline void setText(const WString& text) {
            textLayout.Text = text;
        }

        __declspec(property(get = getText, put = setText)) const WString& Text;

        inline const Color& getTextColor() const {
            return textLayout.Color;
        }

        inline void setTextColor(const Color& color) {
            textLayout.Color = color;
        }

        __declspec(property(get = getTextColor, put = setTextColor)) const Color& TextColor;

        inline TextFormat* getTextFormat() {
            return textLayout.Format;
        }

        inline void setTextFormat(TextFormat* textFormat) {
            textLayout.Format = textFormat;
        }

        __declspec(property(get = getTextFormat, put = setTextFormat)) TextFormat* TextFormat;

        void dispatchContextChanged();

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}