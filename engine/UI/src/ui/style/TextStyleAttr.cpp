#include "ghuipch.h"
#include "TextStyleAttr.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& TextStyleAttr::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextStyleAttr>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& TextStyleValue::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextStyleValue>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& TextStyleRef::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextStyleRef>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	IntrusivePointer<TextStyle> TextStyleRef::resolve(const Theme& theme) const {
		auto it = theme.TextStyles.find(key);
		if (it == theme.TextStyles.end()) {
			Logger::log(LogType::WARNING, std::format(_T("TextStyle '{}' not found in the current theme.\n"), key.Value).c_str());
			return IntrusivePointer<TextStyle>(nullptr);
		}
		return it->value;
    }

}
