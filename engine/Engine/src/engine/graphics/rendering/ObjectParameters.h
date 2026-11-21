#pragma once

#include "core/string/String.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	struct alignas(16) ObjectParameters {
		static const inline AString SRV_NAME = "gh_objectParameters";

		XMFLOAT4X4 world;
	};
}
