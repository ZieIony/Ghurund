#pragma once

#include "Theme.h"

#include "core/object/NotNull.h"
#include "core/resource/ResourceManager.h"
#include "engine/graphics/texture/ITextureFactory.h"

namespace Ghurund::UI {
	class BaseTheme:public Ghurund::UI::Theme {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		
	public:
		BaseTheme(
			Ghurund::Core::ResourceManager& resourceManager,
			ITextureFactory& textureFactory
		);
	};
}