#pragma once

#include "core/object/IntrusivePointer.h"
#include "core/Provider.h"
#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;

	class TextureProvider:public Ghurund::Core::Provider<IntrusivePointer<ITexture>> {};
}