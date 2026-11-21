#include "ghedxpch.h"
#include "IdStreamFactory.h"

namespace Ghurund::Engine::DirectX {
	ComPtr<ID3D12Resource> IdStreamFactory::makeStream(const Array<uint32_t>& data) {
		size_t result = unusedStreams.findBinary([&](const UnusedStreamEntry& item) {return (int)item.size - (int)data.Size; });
		if (result == unusedStreams.Size)
			return memoryManager.makeVertexBuffer(data.Data, data.Size * sizeof(uint32_t));
		if (unusedStreams[result].size > data.Size * 1.2f)
			return memoryManager.makeVertexBuffer(data.Data, data.Size * sizeof(uint32_t));
		// TODO: remove streams unused for longer
		auto resource = unusedStreams[result].resource;
		unusedStreams.removeAt(result);
		return resource;
	}

	void IdStreamFactory::returnStream(size_t size, ComPtr<ID3D12Resource> resource) {
		size_t result = unusedStreams.findBinary([&](const UnusedStreamEntry& item) { return (int)item.size - (int)size; });
		if (result == unusedStreams.Size) {
			unusedStreams.add({ size, resource });
		} else {
			unusedStreams.insert(result, { size, resource });
		}
	}
}
