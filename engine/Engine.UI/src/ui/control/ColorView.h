#pragma once

#include "Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {
	class ColorView :public Control {
	private:
		inline static const auto DEFAULT_COLOR = ColorRef(Theme::COLOR_CONTROL);

		AttrProperty<ColorAttr, Color> color;

	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		ColorView(const ColorAttr& color = DEFAULT_COLOR) :color(color) {}

        inline void setColor(const ColorAttr& color) {
            this->color.set(color);
        }

        __declspec(property(put = setColor)) const ColorAttr& Color;

		virtual void onThemeChanged() override;

		virtual void onDraw(ICanvas& canvas);

		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
	};

	class ColorViewBackgroundStyle :public TypedStyle<ColorView> {

		virtual void apply(ColorView& control) const;
	};

	class ColorViewControlStyle :public TypedStyle<ColorView> {

		virtual void apply(ColorView& control) const;
	};

	class ColorViewAccentStyle :public TypedStyle<ColorView> {

		virtual void apply(ColorView& control) const;
	};
}