#include "ghedxpch.h"
#include "DxMesh.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxMesh::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<DxMesh>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxMesh>()
			.withSupertype(__super::GET_TYPE())
			.withConstructor(CONSTRUCTOR);

		return TYPE;
	}

	void DxMesh::init(DxGPUMemoryManager& memoryManager) {
		if (State != ResourceState::LOADED)
			return;

		memoryManager.resetUpload();
		dataSize.graphical = 0;

		initVertexBuffers(meshData->VertexStreams, meshData->VertexCount, memoryManager);
		initIndexBuffer(meshData->Indices, meshData->IndexCount, memoryManager);
		boundingBox = meshData->BoundingBox;

		memoryManager.executeUploads();

		// sizeof(this) contains indexBuffer and indexBufferView
		dataSize.system = sizeof(this) + meshData->DataSize.system;
		dataSize.system += roles.Size * sizeof(VertexRole);
		dataSize.system += vertexBuffers.Size * sizeof(ComPtr<ID3D12Resource>);
		dataSize.system += vertexBuffersView.Size * sizeof(D3D12_VERTEX_BUFFER_VIEW);
		State = ResourceState::INITIALIZED;
	}

	void DxMesh::initVertexBuffers(const Array<VertexStream>& vertexStreams, uint32_t vertexCount, DxGPUMemoryManager& memoryManager) {
		roles.resize(vertexStreams.Size);
		vertexBuffers.resize(vertexStreams.Size);
		vertexBuffersView.resize(vertexStreams.Size);
		for (size_t i = 0; i < vertexStreams.Size; i++) {
			const VertexStream& stream = vertexStreams[i];

			unsigned int vertexBufferSize = stream.vertexSize * vertexCount;
			// TODO: get the right size from vertexBuffer (alignment and stuff)
			dataSize.graphical += vertexBufferSize;

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
		// TODO: get the right size from indexBuffer (alignment and stuff)
		dataSize.graphical += indexBufferSize;
		this->indexCount = indexCount;
		
		indexBuffer = memoryManager.makeIndexBuffer(buffer);

		indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		size_t indexSize = buffer.Size / indexCount;
		if (indexSize == 4) {
			indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		} else if (indexSize == 2) {
			indexBufferView.Format = DXGI_FORMAT_R16_UINT;
		} else {
			Logger::log(LogType::ERR0R, _T("index size not supported\n"));
			throw InvalidDataException("index size not supported");
		}
		// TODO: check max buffer size
		indexBufferView.SizeInBytes = (UINT)indexBufferSize;
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
		list->IASetVertexBuffers(0, (UINT)bufferViews.Size, &bufferViews[0]);

		list->IASetIndexBuffer(&indexBufferView);
		list->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
	}
}
