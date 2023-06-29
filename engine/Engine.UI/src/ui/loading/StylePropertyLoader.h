#pragma once

#include "PropertyLoader.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {

	class StylePropertyLoader :public PropertyLoader {
	private:
		static inline const char* THEME_STYLE = "theme://style/";

	public:
		virtual const Type& getType() const override {
			return Ghurund::Core::getType<const Style*>();
		}

		virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override {
			AString s = text;
			s.replace('\\', '/');
			uint32_t value = 0;
			if (s.startsWith(THEME_STYLE)) {
				StyleKey styleKey = s.substring(lengthOf(THEME_STYLE));
				auto style = StyleRef(styleKey);
				auto stylePointer = &style;
				property.setRaw(&obj, &stylePointer);
			} else {
				auto text = std::format(_T("Invalid style name: '{}'.\n"), s);
				Logger::log(LogType::WARNING, text.c_str());
			}
		}
	};
}