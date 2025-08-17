#pragma once

#include "VertexStream.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class MeshData:public Resource {
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

		void init(Array<VertexStream> vertexStreams, uint32_t vertexCount, Buffer indices, uint32_t indexCount){
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = indices;
			this->indexCount = indexCount;
		}

		template<typename T>
		void init(Array<VertexStream> vertexStreams, uint32_t vertexCount, const ArrayCollection<T>& indices) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = Buffer(indices.Data, sizeof(T) * indices.Size);
			this->indexCount = (uint32_t)(indices.Size);
		}

		template<typename T>
		void init(Array<VertexStream> vertexStreams, uint32_t vertexCount, const Array<T>& indices) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = Buffer(indices.Data, sizeof(T) * indices.Size);
			this->indexCount = (uint32_t)(indices.Size);
		}

		//virtual bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist);

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

		BoundingBox& getBoundingBox() {
			return boundingBox;
		}

		__declspec(property(get = getBoundingBox)) BoundingBox& BoundingBox;


#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return MeshData::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_MESH = ResourceFormat(L"mesh", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_OBJ = ResourceFormat(L"obj", ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_MESH, FORMAT_OBJ };

		static const inline uint32_t VERSION = 1;
#pragma endregion
	};
}