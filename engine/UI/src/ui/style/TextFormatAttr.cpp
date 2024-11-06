#include "ghuipch.h"
#include "TextFormatAttr.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& TextFormatAttr::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormatAttr>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& TextFormatValue::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormatValue>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& TextFormatRef::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormatRef>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const TextFormat* TextFormatRef::resolve(const Theme& theme) const {
		auto it = theme.TextFormats.find(key);
		if (it == theme.TextFormats.end()) {
			Logger::log(LogType::WARNING, std::format(_T("TextFormat '{}' not found in the current theme.\n"), key.Value).c_str());
			return nullptr;
		}
		return it->value.get();
    }

}
