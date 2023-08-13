#include "ghuipch.h"
#include "ControlContainer.h"

#include "ui/control/InvalidControl.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ControlContainer::GET_TYPE() {

		static auto PROPERTY_CHILD = Property<ControlContainer, Control*>("Child", (Control * (ControlContainer::*)()) & getChild, (void(ControlContainer::*)(Control*)) & setChild);

		static const auto CONSTRUCTOR = Constructor<ControlContainer>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<ControlContainer>(Ghurund::UI::NAMESPACE_NAME, "ControlContainer")
			.withProperty(PROPERTY_CHILD)
			.withConstructor(CONSTRUCTOR)
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

	void ControlContainer::load(LayoutLoader& loader, ResourceManager& resourceManager, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
		__super::load(loader, resourceManager, workingDir, xml);
		auto childElement = xml.FirstChildElement();
		bool childFound = false;
		while (childElement) {
			if (!AString(childElement->Name()).contains(".")) {
				if (childFound) {
					Logger::log(LogType::WARNING, _T("ControlContainer can host only one direct child.\n"));
					return;
				}
				Control* control = loader.loadControl(workingDir, *childElement);
				if (control) {
					Child = control;
				} else {
					Child = ghnew InvalidControl();
				}
				Child->release();
				childFound = true;
			}
			childElement = childElement->NextSiblingElement();
		}
	}
}
