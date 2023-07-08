#include "ghuipch.h"
#include "TextFormatAttr.h"

namespace Ghurund::UI {

    const TextFormat* TextFormatRef::resolve(const Theme& theme) const {
		size_t index = theme.TextFormats.indexOfKey(key);
		if (index == theme.TextFormats.Size) {
			Logger::log(LogType::WARNING, std::format(_T("TextFormat '{}' not found in the current theme.\n"), key.Value).c_str());
			return nullptr;
		}
		return theme.TextFormats.getValue(index).get();
    }

}
