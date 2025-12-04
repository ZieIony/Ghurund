#pragma once

#include "core/Buffer.h"
#include "core/collection/Array.h"
#include "core/collection/ArrayCollection.h"

#include <cstdint>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	enum class VertexRole {
		POSITION, NORMAL, TEXCOORD, TANGENT, COLOR, MIXED
	};

	struct VertexStream {
		Buffer data;
		uint32_t vertexSize;
		VertexRole role;

		VertexStream():data(Buffer()), vertexSize(0), role(VertexRole::MIXED) {}

		VertexStream(const VertexStream& other):data(other.data), vertexSize(other.vertexSize), role(other.role) {}

		VertexStream(VertexStream&& other) noexcept:
			data(std::move(other.data)),
			vertexSize(std::move(other.vertexSize)),
			role(std::move(other.role)) {
		}

		VertexStream(const Buffer& data, uint32_t vertexSize, VertexRole role):data(data), vertexSize(vertexSize), role(role) {}

		template<typename T>
		VertexStream(const Array<T>& data, VertexRole role) : data(Buffer(data.Data, sizeof(T)* data.Size)), vertexSize(sizeof(T)), role(role) {}

		template<typename T>
		VertexStream(const ArrayCollection<T>& data, VertexRole role) : data(Buffer(data.Data, sizeof(T)* data.Size)), vertexSize(sizeof(T)), role(role) {}
	};
}