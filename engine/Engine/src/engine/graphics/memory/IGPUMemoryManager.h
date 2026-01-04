#pragma once

#include "engine/graphics/shader/ConstantBuffer.h"

namespace Ghurund::Engine {
	class IGPUMemoryManager {
	public:
		virtual ~IGPUMemoryManager() = 0 {}

		[[nodiscard]]
		virtual ConstantBuffer* makeConstantBuffer(size_t size) = 0;
	};
}