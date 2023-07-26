#pragma once

#include "ui/theme/Theme.h"

namespace Preview {

	enum class ThemeType {
		LIGHT, DARK
	};

	class ThemeApplication {
	public:
		virtual ~ThemeApplication() = 0 {}

		virtual void setThemeType(ThemeType theme) = 0;

		__declspec(property(put = setThemeType)) ThemeType ThemeType;

		virtual void setPrimaryColor(uint32_t color) = 0;

		__declspec(property(put = setPrimaryColor)) uint32_t PrimaryColor;

		virtual Ghurund::UI::Theme& getCurrentTheme() = 0;

		__declspec(property(get = getCurrentTheme)) Ghurund::UI::Theme& CurrentTheme;
	};
}