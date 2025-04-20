#pragma once

#include "VertexStream.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class Mesh:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Mesh::GET_TYPE();
#pragma endregion

	protected:
		Array<VertexStream> vertexStreams;
		uint32_t vertexCount;
		Buffer indices;
		uint32_t indexCount;

		BoundingBox boundingBox;

		virtual unsigned int getVersion()const {
			return 1;
		}

	public:
		Mesh(Array<VertexStream> vertexStreams, uint32_t vertexCount, Buffer indices, uint32_t indexCount):
			vertexStreams(vertexStreams), vertexCount(vertexCount), indices(indices), indexCount(indexCount) {
		}

		template<typename T>
		Mesh(Array<VertexStream> vertexStreams, uint32_t vertexCount, const ArrayCollection<T>& indices):
			vertexStreams(vertexStreams), vertexCount(vertexCount), indices(Buffer(indices.Data, sizeof(T)* indices.Size)), indexCount((uint32_t)(indices.Size)) {
		}

		/*void removeDuplicates();
		void subdivide();
		void spherify();
		void generateSmoothing(float smoothingTreshold);
		void generateNormals();
		void generateTangents();
		void invertWinding();*/
		void computeBoundingBox();

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
			return Mesh::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_MESH = ResourceFormat(L"mesh", true, true);
		static const inline ResourceFormat FORMAT_OBJ = ResourceFormat(L"obj", true, false);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_MESH, FORMAT_OBJ };
#pragma endregion
	};
}