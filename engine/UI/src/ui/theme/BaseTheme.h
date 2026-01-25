#pragma once

#include "Theme.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	class BaseTheme:public Ghurund::UI::Theme {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		
		IntrusivePointer<TextStyle> makeTextStyle(const wchar_t* style, float size);

	public:
		BaseTheme(Ghurund::Core::ResourceManager& resourceManager);
	};
}