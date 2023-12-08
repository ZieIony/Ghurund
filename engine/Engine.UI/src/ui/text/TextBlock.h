#pragma once

#include "TextLayout.h"
#include "ui/control/Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/TextFormatAttr.h"

namespace Ghurund::UI {
	class TextBlock:public Control {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextBlock::GET_TYPE();
#pragma endregion

	protected:
		AttrProperty<ColorAttr, Color> color;
		Ghurund::UI::TextFormatAttr* textFormat = nullptr;
		Ghurund::UI::TextLayout* textLayout;

		virtual void loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) override;

		virtual void onMeasure() override;

		virtual void onDraw(ICanvas& canvas) override;

		~TextBlock() {
			delete textLayout;
		}

	public:
		TextBlock(std::unique_ptr<Ghurund::UI::TextLayout> textLayout):textLayout(textLayout.release()), color(ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND)) {}

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

		inline void setText(std::unique_ptr<TextDocument> textDocument) {
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

		void setTextFormat(Ghurund::UI::TextFormatAttr* textFormat);

		__declspec(property(get = getTextFormat, put = setTextFormat)) Ghurund::UI::TextFormatAttr* TextFormat;

		void dispatchContextChanged();
	};
}