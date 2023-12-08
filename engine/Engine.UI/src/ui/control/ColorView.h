#pragma once

#include "Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {
	class ColorView:public Control {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ColorView::GET_TYPE();
#pragma endregion

	private:
		inline static const auto DEFAULT_COLOR = ColorRef(Theme::COLOR_CONTROL);

		AttrProperty<ColorAttr, Color> color;

	protected:
		ColorView(const ColorView& other):Control(other), color(other.color) {}

		virtual bool equalsImpl(const Object& other) const override {
			if (__super::equalsImpl(other))
				return true;
			const ColorView& c = (const ColorView&)other;
			return color == c.color;
		}

		virtual void onThemeChanged() override;

		virtual void onDraw(ICanvas& canvas);

	public:
		ColorView(const ColorAttr& color = DEFAULT_COLOR) :color(color) {}

        inline void setColor(const ColorAttr& color) {
            this->color.set(color);
        }

        __declspec(property(put = setColor)) const ColorAttr& Color;

		virtual Object* clone() const {
			return ghnew ColorView(*this);
		}
	};
}