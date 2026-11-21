#pragma once

#include "core/Buffer.h"
#include "core/collection/Array.h"
#include "core/collection/ArrayCollection.h"
#include "engine/graphics/shader/ShaderInputSemantic.h"

#include <cstdint>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	struct VertexStream {
		Buffer data;
		uint32_t vertexSize;
		ShaderInputSemanticEnum semantic;

		VertexStream():data(Buffer()), vertexSize(0), semantic(ShaderInputSemanticEnum::POSITION) {}

		VertexStream(const VertexStream& other):data(other.data), vertexSize(other.vertexSize), semantic(other.semantic) {}

		VertexStream(VertexStream&& other) noexcept:
			data(std::move(other.data)),
			vertexSize(std::move(other.vertexSize)),
			semantic(std::move(other.semantic)) {
		}

		VertexStream(
			const Buffer& data,
			uint32_t vertexSize,
			ShaderInputSemanticEnum semantic):data(data), vertexSize(vertexSize), semantic(semantic) {
		}

		template<typename T>
		VertexStream(
			const Array<T>& data,
			ShaderInputSemanticEnum semantic
		) : data(Buffer(data.Data, sizeof(T)* data.Size)), vertexSize(sizeof(T)), semantic(semantic) {
		}

		template<typename T>
		VertexStream(
			const ArrayCollection<T>& data,
			ShaderInputSemanticEnum semantic
		) : data(Buffer(data.Data, sizeof(T)* data.Size)), vertexSize(sizeof(T)), semantic(semantic) {
		}

		inline uint64_t getDataSize() const {
			return sizeof(*this) + data.Size;
		}
	};
}
