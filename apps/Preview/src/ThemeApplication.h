#pragma once

#include "ui/style/Theme.h"

namespace Preview {

	enum class ThemeType {
		LIGHT, DARK
	};

	__interface ThemeApplication {
		void setThemeType(ThemeType theme);
		__declspec(property(put = setThemeType)) ThemeType ThemeType;

		void setPrimaryColor(uint32_t color);
		__declspec(property(put = setPrimaryColor)) uint32_t PrimaryColor;

		Ghurund::UI::Theme& getCurrentTheme();
		__declspec(property(get = getCurrentTheme)) Ghurund::UI::Theme& CurrentTheme;
	};
}