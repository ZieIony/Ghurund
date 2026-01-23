#pragma once

#include "core/object/IntrusivePointer.h"
#include "core/Provider.h"
#include "ui/material/UIMaterial.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;

	class MaterialProvider:public Ghurund::Core::Provider<UIMaterial*> {};
}