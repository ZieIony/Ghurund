#include "ghuipch.h"
#include "Widget.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/UniqueProperty.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {

	const Ghurund::Core::Type& Widget::GET_TYPE() {
		static auto PROPERTY_IMAGE = UniqueProperty<Widget, std::unique_ptr<Ghurund::UI::LayoutAttr>>("Layout", &setLayout);
		static const Ghurund::Core::Type TYPE = TypeBuilder<Widget>()
			.withProperty(PROPERTY_IMAGE)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void Widget::updateLayout() {
		const UI::Theme* theme = Theme;
		if (theme) {
			this->layout.resolve(*theme);
			if (child != this->layout.get()) {
				setChild(this->layout.get());
				bind();
				onLayoutChanged();
				requestLayout();
			}
		}
	}

	void Widget::onThemeChanged() {
		updateLayout();
		__super::onThemeChanged();
	}

	void Widget::onLoaded() {
		__super::onLoaded();
		if (layout == nullptr)
			Layout = std::make_unique<LayoutRef>(LayoutKey(Type.Name));
	}
}
