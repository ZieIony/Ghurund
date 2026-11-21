#pragma once

#include "core/collection/Array.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"

#include <cstdint>

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class IdStreamFactory {
	private:
		struct UnusedStreamEntry {
			size_t size;
			ComPtr<ID3D12Resource> resource;
		};

		List<UnusedStreamEntry> unusedStreams;
		DxGPUMemoryManager& memoryManager;

	public:
		IdStreamFactory(DxGPUMemoryManager& memoryManager):memoryManager(memoryManager) {}

		ComPtr<ID3D12Resource> makeStream(const Array<uint32_t>& data);

		void returnStream(size_t size, ComPtr<ID3D12Resource> resource);
	};
}
