#pragma once

#include "TextLayout.h"
#include "ui/control/Control.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/Style.h"
#include "ui/style/TextFormatAttr.h"

namespace Ghurund::UI {
    class TextBlock:public Control {
    protected:
        ColorAttr* color = nullptr;
        Ghurund::UI::TextFormatAttr* textFormat = nullptr;
        TextLayout* textLayout;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(ICanvas& canvas) override;

        ~TextBlock() {
            delete textLayout;
            delete color;
        }

    public:
        TextBlock(std::unique_ptr<TextLayout> textLayout):textLayout(textLayout.release()) {
            TextColor = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND);
        }

        /*TextBlock(
            const Ghurund::Core::WString& text,
            const ColorAttr& color = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND),
            TextFormat* textFormat = nullptr
        ):textLayout(text, 0xdd000000, textFormat) {
            TextColor = color;
        }*/

        const TextDocument& getText() {
            return textLayout->TextDocument;
        }

        inline void setText(const Ghurund::Core::WString& text) {
            textLayout->TextDocument = std::move(std::make_unique<TextDocument>(text));
        }

        inline void setText(std::unique_ptr<TextDocument>& textDocument) {
            textLayout->TextDocument = std::move(textDocument);
        }

        __declspec(property(get = getText, put = setText)) const TextDocument& Text;

        inline const ColorAttr& getTextColor() const {
            return *color;
        }

        inline void setTextColor(const ColorAttr& color) {
            delete this->color;
            this->color = (ColorAttr*)color.clone();
        }

        __declspec(property(get = getTextColor, put = setTextColor)) const ColorAttr& TextColor;

        inline Ghurund::UI::TextFormatAttr* getTextFormat() {
            return textFormat;
        }

        inline void setTextFormat(Ghurund::UI::TextFormatAttr* textFormat) {
            if (this->textFormat)
                delete this->textFormat;
            if (textFormat) {
                this->textFormat = (Ghurund::UI::TextFormatAttr*)textFormat->clone();
            } else {
                this->textFormat = nullptr;
            }
            textLayout->Format = textFormat->getValue(*this);
        }

        __declspec(property(get = getTextFormat, put = setTextFormat)) Ghurund::UI::TextFormatAttr* TextFormat;

        void dispatchContextChanged();

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}