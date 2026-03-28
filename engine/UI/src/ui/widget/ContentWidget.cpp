#include "ghuipch.h"
#include "ContentWidget.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/control/InvalidControl.h"

namespace Ghurund::UI {
	void ContentWidget::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const XMLElement& xml) {
		__super::loadInternal(loader, workingDir, xml);
		for (const auto& childElement : xml.children) {
			if (!childElement->name.contains(L".")) {
				try {
					ControlWithConstraints control = loader.loadControl(*this, workingDir, childElement.ref());
					contentConstraints = control.Constraints;
					Content = control.control.get();
				} catch (...) {
					Content = makeIntrusive<InvalidControl>().get();
				}
				return;
			}
		}
	}

	Ghurund::UI::Control* ContentWidget::find(const Ghurund::Core::AString& name) {
		if (this->Name && this->Name->operator==(name))
			return this;
		if (content != nullptr)
			return content->find(name);
		return nullptr;
	}

	Ghurund::UI::Control* ContentWidget::find(const Ghurund::Core::Type& type) {
		if (Type == type)
			return this;
		if (content != nullptr)
			return content->find(type);
		return nullptr;
	}

	const Ghurund::Core::Type& ContentWidget::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ContentWidget>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}