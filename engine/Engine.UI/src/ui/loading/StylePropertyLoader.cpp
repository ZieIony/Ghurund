#include "ghuipch.h"
#include "StylePropertyLoader.h"

namespace Ghurund::UI {
	void StylePropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		s.replace('\\', '/');
		uint32_t value = 0;
		if (s.startsWith(THEME_STYLE)) {
			StyleKey styleKey = s.substring(lengthOf(THEME_STYLE));
			auto style = ghnew StyleRef(styleKey);
			property.setRaw(&obj, &style);
		} else {
			auto text = std::format(_T("Invalid style name: '{}'.\n"), s);
			Logger::log(LogType::WARNING, text.c_str());
		}
	}
}
