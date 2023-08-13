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
		s.replace(L'\\', L'/');
		std::unique_ptr<LayoutAttr> attr;
		if (s.startsWith(THEME_LAYOUT)) {
			LayoutKey layoutKey = s.substring(lengthOf(THEME_LAYOUT));
			attr.reset(ghnew LayoutRef(layoutKey));
		} else {
			ResourcePath path = ResourcePath::parse(convertText<char, wchar_t>(s));
			Control* control = resourceManager.load<Control>(path, workingDir, nullptr, LoadOption::DONT_CACHE);
			attr.reset(ghnew LayoutValue(control));
			control->release();
		}
		if (!attr)
			attr.reset(ghnew LayoutValue(makeShared<InvalidControl>().get()));
		property.setRaw(&obj, &attr);
	}

	void LayoutPropertyLoader::loadChildren(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
		Control* control = layoutLoader.loadControl(workingDir, xml);
		std::unique_ptr<LayoutAttr> attr;
		if (control) {
			attr.reset(ghnew LayoutValue(control));
			control->release();
		} else {
			attr.reset(ghnew LayoutValue(makeShared<InvalidControl>().get()));
		}
		property.setRaw(&obj, &attr);
	}
}