#include "ghuipch.h"
#include "LayoutPropertyLoader.h"

#include "ui/control/InvalidControl.h"
#include "ui/theme/Theme.h"
#include "core/resource/ResourceManager.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/theme/ThemedValue.h"

namespace Ghurund::UI {
	void LayoutPropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		std::unique_ptr<ThemedLayout> layout;
		if (s.startsWith(THEME_LAYOUT)) {
			LayoutKey layoutKey = s.substring(lengthOf(THEME_LAYOUT));
			layout.reset(ghnew ThemedLayout(layoutKey));
		} else {
			FilePath path = FilePath(convertText<char, wchar_t>(s));
			auto coroutine = resourceManager.load<Control>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE);
			coroutine.resume();
			auto control = coroutine.Result;
			layout.reset(ghnew ThemedLayout(control));
		}
		if (!layout)
			layout.reset(ghnew ThemedLayout(IntrusivePointer<Control>(ghnew InvalidControl())));
		property.setRaw(&obj, layout.get());
	}

	void LayoutPropertyLoader::loadChildren(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const XMLElement& xml) const {
		std::unique_ptr<ThemedLayout> layout;
		try {
			ControlWithConstraints control = layoutLoader.loadControl((ControlParent&)obj, workingDir, xml);
			layout.reset(ghnew ThemedLayout(control.control));
		} catch (...) {
			layout.reset(ghnew ThemedLayout(IntrusivePointer<Control>(ghnew InvalidControl())));
		}
		property.setRaw(&obj, layout.get());
	}
}