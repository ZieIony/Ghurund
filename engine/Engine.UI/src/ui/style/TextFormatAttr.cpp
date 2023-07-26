#include "ghuipch.h"
#include "TextFormatAttr.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& TextFormatAttr::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormatAttr>(NAMESPACE_NAME, GH_STRINGIFY(TextFormatAttr))
			.withModifier(TypeModifier::ABSTRACT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

    const TextFormat* TextFormatRef::resolve(const Theme& theme) const {
		size_t index = theme.TextFormats.indexOfKey(key);
		if (index == theme.TextFormats.Size) {
			Logger::log(LogType::WARNING, std::format(_T("TextFormat '{}' not found in the current theme.\n"), key.Value).c_str());
			return nullptr;
		}
		return theme.TextFormats.getValue(index).get();
    }

}
