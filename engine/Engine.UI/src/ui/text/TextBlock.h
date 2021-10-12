#pragma once

#include "TextFormat.h"
#include "TextLayout.h"
#include "ui/control/Control.h"
#include "ui/style/Style.h"
#include "ui/style/ColorAttr.h"

struct IDWriteTextLayout;

namespace Ghurund::UI {
    class TextBlock:public Control {
    protected:
        ColorAttr* color = nullptr;
        TextLayout textLayout;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        static const Ghurund::Core::Type& GET_TYPE();

    public:
        TextBlock():textLayout(L"text", 0xdd000000, nullptr) {
            TextColor = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND);
        }

        TextBlock(
            const Ghurund::Core::WString& text,
            const ColorAttr& color = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND),
            TextFormat* textFormat = nullptr
        ):textLayout(text, 0xdd000000, textFormat) {
            TextColor = color;
        }

        ~TextBlock() {
            delete color;
        }

        const Ghurund::Core::WString& getText() {
            return textLayout.Text;
        }

        inline void setText(const Ghurund::Core::WString& text) {
            textLayout.Text = text;
        }

        __declspec(property(get = getText, put = setText)) const Ghurund::Core::WString& Text;

        inline const ColorAttr& getTextColor() const {
            return *color;
        }

        inline void setTextColor(const ColorAttr& color) {
            delete this->color;
            this->color = (ColorAttr*)color.clone();
        }

        __declspec(property(get = getTextColor, put = setTextColor)) const ColorAttr& TextColor;

        inline TextFormat* getTextFormat() {
            return textLayout.Format;
        }

        inline void setTextFormat(TextFormat* textFormat) {
            textLayout.Format = textFormat;
        }

        __declspec(property(get = getTextFormat, put = setTextFormat)) TextFormat* TextFormat;

        void dispatchContextChanged();

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}