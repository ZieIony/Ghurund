#pragma once

#include "VertexStream.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class MeshData:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = MeshData::GET_TYPE();
#pragma endregion

	protected:
		Array<VertexStream> vertexStreams;
		uint32_t vertexCount = 0;
		Buffer indices;
		uint32_t indexCount = 0;
		BoundingBox boundingBox;

	public:
		MeshData() {}

		void init(
			Array<VertexStream> vertexStreams,
			uint32_t vertexCount,
			Buffer indices,
			uint32_t indexCount,
			const BoundingBox& boundingBox
		) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = indices;
			this->indexCount = indexCount;
			this->boundingBox = boundingBox;
		}

		template<typename T>
		void init(
			Array<VertexStream> vertexStreams,
			uint32_t vertexCount,
			const ArrayCollection<T>& indices,
			const BoundingBox& boundingBox
		) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = Buffer(indices.Data, sizeof(T) * indices.Size);
			this->indexCount = (uint32_t)(indices.Size);
			this->boundingBox = boundingBox;
		}

		template<typename T>
		void init(
			Array<VertexStream> vertexStreams,
			uint32_t vertexCount,
			const Array<T>& indices,
			const BoundingBox& boundingBox
		) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = Buffer(indices.Data, sizeof(T) * indices.Size);
			this->indexCount = (uint32_t)(indices.Size);
			this->boundingBox = boundingBox;
		}

		const Array<VertexStream>& getVertexStreams() const {
			return vertexStreams;
		}

		__declspec(property(get = getVertexStreams)) const Array<VertexStream>& VertexStreams;

		uint32_t getVertexCount() const {
			return vertexCount;
		}

		__declspec(property(get = getVertexCount)) uint32_t VertexCount;

		const Buffer& getIndices() const {
			return indices;
		}

		__declspec(property(get = getIndices)) const Buffer& Indices;

		uint32_t getIndexCount() const {
			return indexCount;
		}

		__declspec(property(get = getIndexCount)) uint32_t IndexCount;

		uint32_t getIndexSize() const {
			return (uint32_t)(indices.Size / indexCount);
		}

		__declspec(property(get = getIndexSize)) uint32_t IndexSize;

		const BoundingBox& getBoundingBox() const {
			return boundingBox;
		}

		__declspec(property(get = getBoundingBox)) const BoundingBox& BoundingBox;

		inline uint64_t getDataSize() const {
			uint64_t size = sizeof(*this) + indices.Size;
			for (auto& stream : vertexStreams)
				size += stream.getDataSize();
			return size;
		}
	};
}
