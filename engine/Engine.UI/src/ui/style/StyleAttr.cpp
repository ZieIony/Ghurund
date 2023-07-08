#include "ghuipch.h"
#include "Style.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {

	const Style* StyleRef::resolve(const Theme& theme) const {
		size_t index = theme.Styles.indexOfKey(key);
		if (index == theme.Styles.Size) {
			Logger::log(LogType::WARNING, std::format(_T("Style '{}' not found in the current theme.\n"), key.Value).c_str());
			return nullptr;
		}
		return theme.Styles.getValue(index);
	}

}
