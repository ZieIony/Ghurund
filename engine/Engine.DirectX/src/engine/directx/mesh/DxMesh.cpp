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

	void DxMesh::init(const MeshData& mesh, NotNull<DxGraphics> graphics, NotNull<CommandList> commandList) {
		if (commandList->State == CommandListState::FINISHED)
			commandList->reset();

		initVertexBuffers(mesh.VertexStreams, mesh.VertexCount, graphics, commandList);
		initIndexBuffer(mesh.Indices, mesh.IndexCount, graphics, commandList);

		commandList->finish();
		commandList->wait();

		uploaded = true;
	}

	void DxMesh::initVertexBuffers(const Array<VertexStream> vertexStreams, uint32_t vertexCount, NotNull<DxGraphics> graphics, NotNull<CommandList> commandList) {
		vertexBuffers.clear();
		for (size_t i = 0; i < vertexStreams.Size;i++) {
			const VertexStream& stream = vertexStreams[i];

			unsigned int vertexBufferSize = stream.vertexSize * vertexCount;

			ComPtr<ID3D12Resource> vertexBuffer;
			auto defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
			auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
			if (FAILED(graphics->Device->CreateCommittedResource(
				&defaultHeapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_COMMON,
				nullptr,
				IID_PPV_ARGS(&vertexBuffer)))) {
				Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
				throw CallFailedException("device->CreateCommittedResource() failed");
			}

			ComPtr<ID3D12Resource> vertexUploadHeap;
			auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			if (FAILED(graphics->Device->CreateCommittedResource(
				&uploadHeapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&vertexUploadHeap)))) {
				Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
				throw CallFailedException("device->CreateCommittedResource() failed");
			}

			D3D12_SUBRESOURCE_DATA vertexData = {};
			vertexData.pData = stream.data.Data;
			vertexData.RowPitch = vertexBufferSize;
			vertexData.SlicePitch = vertexBufferSize;

			// we are now creating a command with the command list to copy the data from
			// the upload heap to the default heap
			UpdateSubresources(commandList->get(), vertexBuffer.Get(), vertexUploadHeap.Get(), 0, 0, 1, &vertexData);

			auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(vertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
			commandList->get()->ResourceBarrier(1, &barrier);

			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
			vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
			vertexBufferView.StrideInBytes = stream.vertexSize;
			vertexBufferView.SizeInBytes = vertexBufferSize;

			// https://github.com/microsoft/DirectXTK12/blob/main/Src/ResourceUploadBatch.cpp
			commandList->addResourceRef(vertexUploadHeap.Get());
			commandList->addResourceRef(vertexBuffer.Get());

			vertexBuffers.add(vertexBuffer);
			vertexBuffersView.add(vertexBufferView);
			vertexUploadHeaps.add(vertexUploadHeap);
		}
	}
	void DxMesh::initIndexBuffer(const Buffer& indices, uint32_t indexCount, NotNull<DxGraphics> graphics, NotNull<CommandList> commandList) {
		unsigned int indexBufferSize = indices.Size;
		this->indexCount = indexCount;

		auto defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
		if (FAILED(graphics->Device->CreateCommittedResource(
			&defaultHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_COMMON,
			nullptr,
			IID_PPV_ARGS(&indexBuffer)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
			throw CallFailedException("device->CreateCommittedResource() failed");
		}

		auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		if (FAILED(graphics->Device->CreateCommittedResource(
			&uploadHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&indexUploadHeap)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
			throw CallFailedException("device->CreateCommittedResource() failed");
		}

		D3D12_SUBRESOURCE_DATA indexData = {};
		indexData.pData = indices.Data;
		indexData.RowPitch = indexBufferSize;
		indexData.SlicePitch = indexBufferSize;

		// we are now creating a command with the command list to copy the data from
		// the upload heap to the default heap
		UpdateSubresources(commandList->get(), indexBuffer.Get(), indexUploadHeap.Get(), 0, 0, 1, &indexData);

		auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(indexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
		commandList->get()->ResourceBarrier(1, &barrier);

		indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		uint8_t indexSize = indices.Size / indexCount;
		if (indexSize == 4) {
			indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		} else if (indexSize == 2) {
			indexBufferView.Format = DXGI_FORMAT_R16_UINT;
		} else {
			Logger::log(LogType::ERR0R, _T("index size not supported\n"));
			throw InvalidDataException("index size not supported");
		}
		indexBufferView.SizeInBytes = indexBufferSize;

		commandList->addResourceRef(indexUploadHeap.Get());
		commandList->addResourceRef(indexBuffer.Get());
	}

	void DxMesh::draw(CommandList& commandList) {
		commandList.addPointerRef(this);
		ID3D12GraphicsCommandList* list = commandList.get();
		list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		list->IASetVertexBuffers(0, vertexBuffersView.Size, &vertexBuffersView[0]);
		list->IASetIndexBuffer(&indexBufferView);
		list->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
	}
}