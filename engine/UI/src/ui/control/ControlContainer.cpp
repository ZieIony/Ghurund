#include "ghuipch.h"
#include "ControlContainer.h"

#include "ui/control/InvalidControl.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ControlContainer::GET_TYPE() {

		static const Ghurund::Core::Type TYPE = TypeBuilder<ControlContainer>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	Control* ControlContainer::find(const AString& name) {
		if (this->Name && this->Name->operator==(name))
			return this;
		if (child)
			return child->find(name);
		return nullptr;
	}

	Control* ControlContainer::find(const Ghurund::Core::Type& type) {
		if (Type == type)
			return this;
		if (child)
			return child->find(type);
		return nullptr;
	}

	void ControlContainer::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
		__super::loadInternal(loader, workingDir, xml);
		auto childElement = xml.FirstChildElement();
		bool childFound = false;
		while (childElement) {
			if (!AString(childElement->Name()).contains(".")) {
				if (childFound) {
					Logger::log(LogType::WARNING, _T("ControlContainer can host only one direct child.\n"));
					return;
				}
				try {
					ControlWithConstraints control = loader.loadControl(*this, workingDir, *childElement);
					Child = control.control.get();	// this sets constraints too
					setConstraints(*control.control.get(), control.Constraints);
				} catch (...) {
					Child = ghnew InvalidControl();	// this sets constraints too
				}
				childFound = true;
			}
			childElement = childElement->NextSiblingElement();
		}
	}
}
