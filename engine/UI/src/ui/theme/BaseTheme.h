#pragma once

#include "Theme.h"

#include "core/NotNull.h"
#include "core/resource/ResourceManager.h"
#include "ui/loading/IDrawableFactory.h"
#include "ui/image/BitmapFactory.h"

namespace Ghurund::UI {
	class BaseTheme:public Ghurund::UI::Theme {
	private:
		// borrowed
		Ghurund::Core::ResourceManager* resourceManager;
		
	public:
		BaseTheme(
			NotNull<Ghurund::Core::ResourceManager> resourceManager,
			NotNull<Ghurund::UI::IDrawableFactory> drawableFactory
		);
	};
}