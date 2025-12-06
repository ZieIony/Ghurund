#pragma once

#include "core/object/IntrusivePointer.h"
#include "core/Provider.h"
#include "engine/graphics/material/IMaterial.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;

	class MaterialProvider:public Ghurund::Core::Provider<IntrusivePointer<IMaterial>> {};
}