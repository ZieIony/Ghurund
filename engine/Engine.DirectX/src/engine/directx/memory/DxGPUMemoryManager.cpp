#include "ghedxpch.h"
#include "DxGPUMemoryManager.h"

#include "core/math/MathUtils.h"
#include "engine/directx/DxGraphics.h"
#include "core/logging/Logger.h"
#include "engine/directx/shader/DxConstantBuffer.h"

namespace Ghurund::Engine::DirectX {
    DxGPUMemoryManager::DxGPUMemoryManager(
		DxGraphics& graphics,
		CommandList& uploadCommandList
	):graphics(graphics), uploadCommandList(uploadCommandList) {
        depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
        depthClearValue.DepthStencil.Depth = 1.0f;
        depthClearValue.DepthStencil.Stencil = 0;

        HeapAllocator* uploadAllocator = ghnew HeapAllocator(graphics, 100_MB, nullptr,
            D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES | D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES);
        allocators.put(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD, uploadAllocator);
        HeapAllocator* defaultAllocator = ghnew HeapAllocator(graphics, 100_MB, nullptr,
            D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_DENY_BUFFERS | D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES);
        allocators.put(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT, defaultAllocator);
    }

    GPUResourcePointer* DxGPUMemoryManager::makePlacedResource(
        D3D12_HEAP_TYPE heapType,
        CD3DX12_RESOURCE_DESC resourceDesc,
        D3D12_RESOURCE_STATES initialState,
        ID3D12Resource** resource
    ) {
        HeapAllocator* heap = allocators.get(heapType);
        void* address = (void*)heap->allocate(resourceDesc.Width);
        if ((uint64_t)address == heap->Size) {
            Logger::log(LogType::ERR0R, _T("failed to allocate memory for resource\n"));
            return nullptr;
        }
        if (FAILED(graphics.Device->CreatePlacedResource(heap->Heap, (uint64_t)address, &resourceDesc, initialState, resourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER ? nullptr : &depthClearValue, IID_PPV_ARGS(resource)))) {
            Logger::log(LogType::ERR0R, _T("failed to create placed resource\n"));
            return nullptr;
        }

        return ghnew GPUResourcePointer(heap, address, *resource);
    }

	ComPtr<ID3D12Resource> DxGPUMemoryManager::makeUploadResource(
		size_t size,
		CommandList& commandList,
		D3D12_RESOURCE_STATES resourceType
	) {
		auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(size);

		ComPtr<ID3D12Resource> uploadHeap;
		auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		if (FAILED(graphics.Device->CreateCommittedResource(
			&uploadHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			resourceType,
			nullptr,
			IID_PPV_ARGS(&uploadHeap)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
			throw CallFailedException("device->CreateCommittedResource() failed");
		}

		commandList.addResourceRef(uploadHeap.Get());

		return uploadHeap;
	}

	ComPtr<ID3D12Resource> DxGPUMemoryManager::makeCommitedResource(
		const Buffer& buffer,
		CommandList& commandList,
		D3D12_RESOURCE_STATES resourceType
    ) {
		ComPtr<ID3D12Resource> resource;
		auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(buffer.Size);

		auto defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		if (FAILED(graphics.Device->CreateCommittedResource(
			&defaultHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_COMMON,
			nullptr,
			IID_PPV_ARGS(&resource)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
			throw CallFailedException("device->CreateCommittedResource() failed");
		}

		ComPtr<ID3D12Resource> uploadHeap;
		auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		if (FAILED(graphics.Device->CreateCommittedResource(
			&uploadHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&uploadHeap)))) {
			Logger::log(LogType::ERR0R, _T("device->CreateCommittedResource() failed\n"));
			throw CallFailedException("device->CreateCommittedResource() failed");
		}

		D3D12_SUBRESOURCE_DATA vertexData = {};
		vertexData.pData = buffer.Data;
		vertexData.RowPitch = buffer.Size;
		vertexData.SlicePitch = buffer.Size;

		// we are now creating a command with the command list to copy the data from
		// the upload heap to the default heap
		UpdateSubresources(commandList.get(), resource.Get(), uploadHeap.Get(), 0, 0, 1, &vertexData);

		auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(resource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, resourceType);
		commandList.get()->ResourceBarrier(1, &barrier);

		// https://github.com/microsoft/DirectXTK12/blob/main/Src/ResourceUploadBatch.cpp
		commandList.addResourceRef(resource.Get());
		commandList.addResourceRef(uploadHeap.Get());

		return resource;
	}

    ConstantBuffer* DxGPUMemoryManager::makeConstantBuffer(size_t size) {
		auto uploadHeap = makeUploadResource(align<size_t>(size, 256), uploadCommandList, D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE);
        auto cb = ghnew DxConstantBuffer();
        cb->init(uploadHeap);
        return cb;
	}

    ComPtr<ID3D12Resource> DxGPUMemoryManager::makeVertexBuffer(const Buffer& buffer) {
		return makeCommitedResource(buffer, uploadCommandList, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	}

	ComPtr<ID3D12Resource> DxGPUMemoryManager::makeIndexBuffer(const Buffer& buffer) {
		return makeCommitedResource(buffer, uploadCommandList, D3D12_RESOURCE_STATE_INDEX_BUFFER);
	}
}