#pragma once

#include "TextLayout.h"
#include "TextLayoutConstraint.h"
#include "ui/control/Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/FontAttr.h"

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
		Ghurund::UI::FontAttr* font = nullptr;
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
			Font* font = nullptr
		):textLayout(typeName, 0xdd000000, font) {
			TextColor = color;
		}*/

		~TextBlock() {
			if (font)
				delete font;
		}

		TextDocument* getDocument() {
			return textLayout.Document;
		}

		inline void setDocument(TextDocument* textDocument) {
			textLayout.Document = textDocument;
		}

		__declspec(property(get = getDocument, put = setDocument)) TextDocument* Document;

		inline void setTextColor(const ColorAttr& color) {
			this->color.set(color);
		}

		__declspec(property(put = setTextColor)) const ColorAttr& TextColor;

		inline Ghurund::UI::FontAttr* getFont() {
			return font;
		}

		void setFont(Ghurund::UI::FontAttr* font);

		__declspec(property(get = getFont, put = setFont)) Ghurund::UI::FontAttr* Font;

		void dispatchContextChanged();
	};
}