#pragma once

#include "core/string/String.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	struct GlobalParameters {
		static const inline AString CB_NAME = "GlobalParams";

		__declspec(align(4)) float time;
		__declspec(align(4)) XMFLOAT3 cameraPos;
		__declspec(align(8)) XMINT2 mousePos;
		__declspec(align(8)) XMINT2 viewportSize;
		__declspec(align(16)) XMFLOAT4X4 viewProj;
	};
}
