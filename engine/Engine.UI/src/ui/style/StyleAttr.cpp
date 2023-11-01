#include "ghuipch.h"
#include "Style.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& StyleAttr::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<StyleAttr>(NAMESPACE_NAME, GH_STRINGIFY(StyleAttr))
			.withModifier(TypeModifier::ABSTRACT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Style* StyleRef::resolve(const Theme& theme) const {
		auto it = theme.Styles.find(key);
		if (it == theme.Styles.end()) {
			Logger::log(LogType::WARNING, std::format(_T("Style '{}' not found in the current theme.\n"), key.Value).c_str());
			return nullptr;
		}
		return it->value;
	}

}
