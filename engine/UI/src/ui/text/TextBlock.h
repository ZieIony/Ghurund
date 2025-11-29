#pragma once

#include "TextLayout.h"
#include "TextLayoutConstraint.h"
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
		Ghurund::UI::TextLayout textLayout;

		virtual void loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) override;

		//virtual void onMeasure() override;

		virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

	public:
		TextBlock():color(ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND)) {
			contentSize = Ghurund::UI::ContentSize(
				makeIntrusive<TextLayoutWidthConstraint>(textLayout).get(),
				makeIntrusive<TextLayoutHeightConstraint>(textLayout).get()
			);
		}

		/*TextBlock(
			const Ghurund::Core::WString& typeName,
			const ColorAttr& color = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND),
			TextFormat* textFormat = nullptr
		):textLayout(typeName, 0xdd000000, textFormat) {
			TextColor = color;
		}*/

		~TextBlock() {
			if (textFormat)
				delete textFormat;
		}

		const TextDocument& getText() {
			return textLayout.TextDocument;
		}

		inline void setText(const Ghurund::Core::WString& text) {
			textLayout.TextDocument = text;
		}

		inline void setText(const TextDocument& textDocument) {
			textLayout.TextDocument = textDocument;
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