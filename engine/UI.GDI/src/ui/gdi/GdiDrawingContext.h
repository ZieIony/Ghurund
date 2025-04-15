#pragma once

#include "core/reflection/Type.h"

namespace Ghurund::UI::GDI {
	class GdiDrawingContext {
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::GDI::GdiDrawingContext>();
}