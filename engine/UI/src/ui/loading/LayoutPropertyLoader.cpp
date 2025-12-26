#include "ghuipch.h"
#include "LayoutPropertyLoader.h"

#include "ui/control/InvalidControl.h"
#include "ui/style/LayoutAttr.h"
#include "ui/theme/Theme.h"
#include "core/resource/ResourceManager.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
	void LayoutPropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		std::unique_ptr<LayoutAttr> attr;
		if (s.startsWith(THEME_LAYOUT)) {
			LayoutKey layoutKey = s.substring(lengthOf(THEME_LAYOUT));
			attr.reset(ghnew LayoutRef(layoutKey));
		} else {
			FilePath path = FilePath(convertText<char, wchar_t>(s));
			Control* control = resourceManager.load<Control>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE);
			attr.reset(ghnew LayoutValue(control));
			control->release();
		}
		if (!attr)
			attr.reset(ghnew LayoutValue(makeIntrusive<InvalidControl>().get()));
		property.setRaw(&obj, &attr);
	}

	void LayoutPropertyLoader::loadChildren(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
		std::unique_ptr<LayoutAttr> attr;
		try {
			ControlWithConstraints control = layoutLoader.loadControl((ControlParent&)obj, workingDir, xml);
			attr.reset(ghnew LayoutValue(control.control.get()));
		} catch (...) {
			attr.reset(ghnew LayoutValue(makeIntrusive<InvalidControl>().get()));
		}
		property.setRaw(&obj, &attr);
	}
}