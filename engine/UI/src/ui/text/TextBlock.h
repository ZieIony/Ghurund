#pragma once

#include "TextLayout.h"
#include "TextLayoutConstraint.h"

#include "ui/control/Control.h"
#include "ui/theme/Theme.h"
#include "ui/theme/ThemedValueProperty.h"

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
		ThemedValueProperty<ColorKey, Color> color;
		ThemedValueProperty<TextStyleKey, IntrusivePointer<TextStyle>> textStyle;
		TextLayout textLayout;

		void refreshLayout();

		virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

		inline void setThemedTextColor(const ThemedColor& color) {
			if (color.Key) {
				setTextColor(*color.Key);
			} else {
				setTextColor(color.Value);
			}
		}

		inline void setThemedTextStyle(const ThemedTextStyle& textStyle) {
			if (textStyle.Key) {
				setTextStyle(*textStyle.Key);
			} else {
				setTextStyle(textStyle.Value);
			}
		}

	public:
		TextBlock():color(Theme::COLOR_PRIMARY_ONBACKGROUND) {
			contentSize = Ghurund::UI::ContentSize(
				makeIntrusive<TextLayoutWidthConstraint>(textLayout).get(),
				makeIntrusive<TextLayoutHeightConstraint>(textLayout).get()
			);
			setTextStyle(Theme::TEXT_STYLE_TEXT_SECONDARY);
		}

		const WString& getText() {
			return text;
		}

		inline void setText(const WString& text) {
			this->text = text;
			refreshLayout();
		}

		__declspec(property(get = getText, put = setText)) const WString& Text;

		inline void setTextColor(const Color& color) {
			this->color.set(color);
			refreshLayout();
		}

		inline void setTextColor(const ColorKey& color) {
			this->color.set(color);
			refreshLayout();
		}

		__declspec(property(put = setTextColor)) const Color& TextColor;

		void setTextStyle(Ghurund::UI::TextStyleKey textStyle);

		void setTextStyle(IntrusivePointer<Ghurund::UI::TextStyle> textStyle);

		__declspec(property(put = setTextStyle)) IntrusivePointer<Ghurund::UI::TextStyle> TextStyle;

		void dispatchContextChanged();
	};
}