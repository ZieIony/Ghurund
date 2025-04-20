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

	void DxMesh::init(Graphics& graphics, CommandList& commandList, unsigned int detail) {
		if (commandList.State == CommandListState::FINISHED)
			commandList.reset();

		initVertexBuffers(graphics, commandList);
		initIndexBuffer(graphics, commandList);

		commandList.finish();
		commandList.wait();

		uploaded = true;
	}

	void DxMesh::initVertexBuffers(Graphics& graphics, CommandList& commandList) {
		for (size_t i = 0; i < vertexStreams.Size;i++) {
			VertexStream& stream = vertexStreams[i];

			unsigned int vertexBufferSize = stream.vertexSize * vertexCount;

			auto defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
			auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
			if (FAILED(graphics.Device->CreateCommittedResource(
				&defaultHeapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(&vertexBuffer[i])))) {
				Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
				throw CallFailedException("device->CreateCommittedResource() failed");
			}

			auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			if (FAILED(graphics.Device->CreateCommittedResource(
				&uploadHeapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&vertexUploadHeap[i])))) {
				Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
				throw CallFailedException("device->CreateCommittedResource() failed");
			}

			D3D12_SUBRESOURCE_DATA vertexData = {};
			vertexData.pData = stream.data.Data;
			vertexData.RowPitch = vertexBufferSize;
			vertexData.SlicePitch = vertexBufferSize;

			// we are now creating a command with the command list to copy the data from
			// the upload heap to the default heap
			UpdateSubresources(commandList.get(), vertexBuffer[i].Get(), vertexUploadHeap[i].Get(), 0, 0, 1, &vertexData);

			auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(vertexBuffer[i].Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
			commandList.get()->ResourceBarrier(1, &barrier);

			vertexBufferView[i].BufferLocation = vertexBuffer[i]->GetGPUVirtualAddress();
			vertexBufferView[i].StrideInBytes = stream.vertexSize;
			vertexBufferView[i].SizeInBytes = vertexBufferSize;

			commandList.addResourceRef(vertexUploadHeap[i].Get());
			commandList.addResourceRef(vertexBuffer[i].Get());
		}
	}
	void DxMesh::initIndexBuffer(Graphics& graphics, CommandList& commandList) {
		unsigned int indexBufferSize = sizeof(unsigned int) * indices.Size;

		auto defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
		if (FAILED(graphics.Device->CreateCommittedResource(
			&defaultHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&indexBuffer)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
			throw CallFailedException("device->CreateCommittedResource() failed");
		}

		auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		if (FAILED(graphics.Device->CreateCommittedResource(
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
		UpdateSubresources(commandList.get(), indexBuffer.Get(), indexUploadHeap.Get(), 0, 0, 1, &indexData);

		auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(indexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
		commandList.get()->ResourceBarrier(1, &barrier);

		indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		indexBufferView.SizeInBytes = indexBufferSize;

		commandList.addResourceRef(indexUploadHeap.Get());
		commandList.addResourceRef(indexBuffer.Get());
	}

	void DxMesh::draw(CommandList& commandList) {
		commandList.addPointerRef(this);
		ID3D12GraphicsCommandList* list = commandList.get();
		list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		list->IASetVertexBuffers(0, vertexBufferView.Size, &vertexBufferView[0]);
		list->IASetIndexBuffer(&indexBufferView);
		list->DrawIndexedInstanced(indices.Size, 1, 0, 0, 0);
	}
}