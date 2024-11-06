#include "ghuipch.h"
#include "LayoutAttr.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& LayoutAttr::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<LayoutAttr>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& LayoutValue::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<LayoutValue>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Ghurund::Core::Type& LayoutRef::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<LayoutRef>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	IntrusivePointer<Control> LayoutRef::resolve(const Theme& theme) const {
		auto iterator = theme.Layouts.find(key);
		if (iterator == theme.Layouts.end()) {
			Logger::log(LogType::WARNING, std::format(_T("Layout '{}' not found in the current theme.\n"), key.Value).c_str());
			return IntrusivePointer<Control>(nullptr);
		}
		return iterator->value->get();
	}
}
