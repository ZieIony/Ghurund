#include "ghedxpch.h"
#include "DxMesh.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxMesh::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxMesh>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void DxMesh::init(const MeshData& mesh, DxGPUMemoryManager& memoryManager) {
		memoryManager.resetUpload();

		initVertexBuffers(mesh.VertexStreams, mesh.VertexCount, memoryManager);
		initIndexBuffer(mesh.Indices, mesh.IndexCount, memoryManager);

		memoryManager.executeUploads();
	}

	void DxMesh::initVertexBuffers(const Array<VertexStream>& vertexStreams, uint32_t vertexCount, DxGPUMemoryManager& memoryManager) {
		roles.clear();
		vertexBuffers.clear();
		vertexBuffersView.clear();
		for (size_t i = 0; i < vertexStreams.Size; i++) {
			const VertexStream& stream = vertexStreams[i];

			unsigned int vertexBufferSize = stream.vertexSize * vertexCount;

			ComPtr<ID3D12Resource> vertexBuffer = memoryManager.makeVertexBuffer(stream.data);

			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
			vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
			vertexBufferView.StrideInBytes = stream.vertexSize;
			vertexBufferView.SizeInBytes = vertexBufferSize;

			roles.add(stream.role);
			vertexBuffers.add(vertexBuffer);
			vertexBuffersView.add(vertexBufferView);
		}
	}

	void DxMesh::initIndexBuffer(const Buffer& buffer, uint32_t indexCount, DxGPUMemoryManager& memoryManager) {
		size_t indexBufferSize = buffer.Size;
		this->indexCount = indexCount;
		
		indexBuffer = memoryManager.makeIndexBuffer(buffer);

		indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		uint8_t indexSize = buffer.Size / indexCount;
		if (indexSize == 4) {
			indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		} else if (indexSize == 2) {
			indexBufferView.Format = DXGI_FORMAT_R16_UINT;
		} else {
			Logger::log(LogType::ERR0R, _T("index size not supported\n"));
			throw InvalidDataException("index size not supported");
		}
		indexBufferView.SizeInBytes = indexBufferSize;
	}

	void DxMesh::draw(CommandList& commandList, const Array<VertexRole>& layout) {
		commandList.addPointerRef(this);
		ID3D12GraphicsCommandList* list = commandList.get();
		list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Array<D3D12_VERTEX_BUFFER_VIEW> bufferViews(layout.Size);
		for (size_t j = 0; j < layout.Size; j++) {
			for (size_t i = 0; i < roles.Size; i++) {
				if (roles[i] == layout[j]) {
					bufferViews[j] = vertexBuffersView[i];
					break;
				}
			}
		}
		list->IASetVertexBuffers(0, bufferViews.Size, &bufferViews[0]);

		list->IASetIndexBuffer(&indexBufferView);
		list->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
	}
}