#include "ghuipch.h"
#include "Widget.h"

#include "core/string/TextConversionUtils.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/UniqueProperty.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Style.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {

	const Ghurund::Core::Type& Widget::GET_TYPE() {
		static auto PROPERTY_IMAGE = UniqueProperty<Widget, std::unique_ptr<Ghurund::UI::LayoutAttr>>("Layout", &setLayout);
		static const Ghurund::Core::Type TYPE = TypeBuilder<Widget>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(Widget))
			.withProperty(PROPERTY_IMAGE)
			.withModifiers(TypeModifier::ABSTRACT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void Widget::updateLayout() {
		const UI::Theme* theme = Theme;
		if (theme) {
			this->layout.resolve(*theme);
			if (child != this->layout.get()) {
				setChild(this->layout.get());
				onLayoutChanged();
				requestLayout();
			}
		}
	}

	void Widget::onThemeChanged() {
		updateLayout();
		__super::onThemeChanged();
	}

	Control* Widget::find(const AString& name) {
		if (this->Name && this->Name->operator==(name))
			return this;
		return nullptr;
	}

	Control* Widget::find(const Ghurund::Core::Type& type) {
		if (Type == type)
			return this;
		return nullptr;
	}

	void Widget::load(LayoutLoader& loader, ResourceManager& resourceManager, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
		Control::load(loader, resourceManager, workingDir, xml);
		if (style == nullptr)
			Style = std::move(std::make_unique<StyleRef>(StyleKey(Type.Name)));
		if (layout == nullptr)
			Layout = std::make_unique<LayoutRef>(LayoutKey(Type.Name));
	}
}
