#include "ghuipch.h"
#include "FontAttr.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& FontAttr::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<FontAttr>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& FontValue::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<FontValue>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& FontRef::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<FontRef>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Font* FontRef::resolve(const Theme& theme) const {
		auto it = theme.Fonts.find(key);
		if (it == theme.Fonts.end()) {
			Logger::log(LogType::WARNING, std::format(_T("Font '{}' not found in the current theme.\n"), key.Value).c_str());
			return nullptr;
		}
		return it->value.get();
    }

}
