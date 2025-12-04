#pragma once

#include "core/Buffer.h"
#include "core/string/String.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	struct ShaderCompilationResult {
		Buffer data;
		AString logs;
		uint32_t errorCode;
	};
}