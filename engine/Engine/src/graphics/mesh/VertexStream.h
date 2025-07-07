#pragma once

#include <core/Buffer.h>
#include <core/collection/List.h>
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

		VertexStream(const Buffer& data, uint32_t vertexSize, VertexRole role):data(data), vertexSize(vertexSize), role(role) {}

		template<typename T>
		VertexStream(const ArrayCollection<T>& data, VertexRole role):data(Buffer(data.Data, sizeof(T)* data.Size)), vertexSize(sizeof(T)), role(role) {}
	};
}