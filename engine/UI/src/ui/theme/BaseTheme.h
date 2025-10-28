#pragma once

#include "Theme.h"

#include "core/object/NotNull.h"
#include "core/resource/ResourceManager.h"
#include "ui/loading/IDrawableFactory.h"
#include "ui/image/BitmapFactory.h"

namespace Ghurund::UI {
	class BaseTheme:public Ghurund::UI::Theme {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		
	public:
		BaseTheme(
			Ghurund::Core::ResourceManager& resourceManager,
			Ghurund::UI::IDrawableFactory& drawableFactory
		);
	};
}