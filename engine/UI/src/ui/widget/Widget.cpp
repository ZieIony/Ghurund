#include "ghuipch.h"
#include "Widget.h"

#include "core/reflection/TypeBuilder.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	template<>
	IntrusivePointer<Control> resolveThemeValue(const Theme& theme, const LayoutKey& key) {
		auto iterator = theme.Layouts.find(key);
		if (iterator == theme.Layouts.end()) {
			Logger::log(LogType::WARNING, std::format(_T("Layout '{}' not found in the current theme.\n"), key.Value).c_str());
			return IntrusivePointer<Control>(nullptr);
		}
		return iterator->value->get();
	}

	const Ghurund::Core::Type& Widget::GET_TYPE() {
		static auto PROPERTY_IMAGE = Property<Widget, const ThemedLayout&>("Layout", &setThemedLayout);
		static const Ghurund::Core::Type TYPE = TypeBuilder<Widget>()
			.withProperty(PROPERTY_IMAGE)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void Widget::updateLayout() {
		const UI::Theme* theme = Theme;
		if (theme) {
			this->layout.resolve(*theme);
			if (child != this->layout.get().get()) {
				setChild(this->layout.get().get());
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
		if (layout.get() == nullptr)
			Layout = LayoutKey(Type.Name);
	}
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::ThemedLayout>() {
		static Type TYPE = TypeBuilder<Ghurund::UI::ThemedLayout>();
		return TYPE;
	}
}
