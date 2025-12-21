#pragma once

#include "TextLayout.h"
#include "TextLayoutConstraint.h"
#include "ui/control/Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/TextStyleAttr.h"
#include "ui/style/PointerAttrProperty.h"

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

	private:
		WString text;
		AttrProperty<ColorAttr, Color> color;
		PointerAttrProperty<TextStyleAttr, TextStyle> textStyle;
		TextLayout textLayout;

		void refreshLayout();

		virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

	public:
		TextBlock():color(ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND)) {
			contentSize = Ghurund::UI::ContentSize(
				makeIntrusive<TextLayoutWidthConstraint>(textLayout).get(),
				makeIntrusive<TextLayoutHeightConstraint>(textLayout).get()
			);
			setTextStyle(std::make_unique<TextStyleRef>(Theme::TEXT_STYLE_TEXT_SECONDARY));
		}

		const WString& getText() {
			return text;
		}

		inline void setText(const WString& text) {
			this->text = text;
			refreshLayout();
		}

		__declspec(property(get = getText, put = setText)) const WString& Text;

		inline void setTextColor(const ColorAttr& color);

		__declspec(property(put = setTextColor)) const ColorAttr& TextColor;

		void setTextStyle(std::unique_ptr<Ghurund::UI::TextStyleAttr> textStyle);

		__declspec(property(put = setTextStyle)) std::unique_ptr<Ghurund::UI::TextStyleAttr> TextStyle;

		void dispatchContextChanged();
	};
}