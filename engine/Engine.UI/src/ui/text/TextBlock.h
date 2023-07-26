#pragma once

#include "TextLayout.h"
#include "ui/control/Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/Style.h"
#include "ui/style/TextFormatAttr.h"

namespace Ghurund::UI {
	class TextBlock:public Control {
	protected:
		AttrProperty<ColorAttr, Color> color;
		Ghurund::UI::TextFormatAttr* textFormat = nullptr;
		TextLayout* textLayout;

		virtual void onMeasure() override;

		virtual void onDraw(ICanvas& canvas) override;

		~TextBlock() {
			delete textLayout;
		}

	public:
		TextBlock(std::unique_ptr<TextLayout> textLayout):textLayout(textLayout.release()), color(ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND)) {}

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

		inline void setTextColor(const ColorAttr& color) {
			this->color.set(color);
		}

		__declspec(property(put = setTextColor)) const ColorAttr& TextColor;

		inline Ghurund::UI::TextFormatAttr* getTextFormat() {
			return textFormat;
		}

		inline void setTextFormat(Ghurund::UI::TextFormatAttr* textFormat) {
			if (this->textFormat)
				delete this->textFormat;
			if (textFormat) {
				this->textFormat = (Ghurund::UI::TextFormatAttr*)textFormat->clone();
				auto theme = Theme;
				if (theme)
					textLayout->Format = textFormat->resolve(*theme);
			} else {
				this->textFormat = nullptr;
				textLayout->Format = nullptr;
			}
		}

		__declspec(property(get = getTextFormat, put = setTextFormat)) Ghurund::UI::TextFormatAttr* TextFormat;

		void dispatchContextChanged();

		virtual void load(LayoutLoader& loader, ResourceManager& resourceManager, const tinyxml2::XMLElement& xml) override;

		static const Ghurund::Core::Type& GET_TYPE();

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;
	};
}