#pragma once

#include "GPUResourcePointer.h"
#include "HeapAllocator.h"

#include "core/Buffer.h"
#include "core/collection/Map.h"
#include "engine/directx/CommandList.h"
#include "engine/graphics/memory/IGPUMemoryManager.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <d3dx12.h>
#include <wrl.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
    using namespace Microsoft::WRL;

	class DxGPUMemoryManager:public IGPUMemoryManager {
    private:
        DxGraphics& graphics;
        CommandList& uploadCommandList;

        // for placed resources:
        Map<D3D12_HEAP_TYPE, HeapAllocator*> allocators;

        D3D12_CLEAR_VALUE depthClearValue = {};

    public:
        DxGPUMemoryManager(DxGraphics& graphics, CommandList& uploadCommandList);

        ~DxGPUMemoryManager() {
            for (auto& [heapType, allocator] : allocators)
                delete allocator;
        }

        // placed resources are light and fast, but require manual GPU memory management - too complicated for now
        GPUResourcePointer* makePlacedResource(D3D12_HEAP_TYPE heapType, CD3DX12_RESOURCE_DESC resourceDesc, D3D12_RESOURCE_STATES initialState, ID3D12Resource** resource);

        ComPtr<ID3D12Resource> makeUploadResource(size_t size, CommandList& commandList, D3D12_RESOURCE_STATES resourceType);

        ComPtr<ID3D12Resource> makeCommitedResource(const Buffer& buffer, CommandList& commandList, D3D12_RESOURCE_STATES resourceType);

        uint64_t getSize() {
            uint64_t size = 0;
            for (auto& [heapType, allocator] : allocators)
                size += allocator->Size;
            return size;
        }

        __declspec(property(get = getSize)) uint64_t Size;

        uint64_t getAllocated() {
            uint64_t allocated = 0;
            for (auto& [heapType, allocator] : allocators)
                allocated += allocator->Allocated;
            return allocated;
        }

        __declspec(property(get = getAllocated)) uint64_t Allocated;

        [[nodiscard]]
        virtual ConstantBuffer* makeConstantBuffer(size_t size) override;

        ComPtr<ID3D12Resource> makeVertexBuffer(const Buffer& buffer);

        ComPtr<ID3D12Resource> makeIndexBuffer(const Buffer& buffer);

        inline void resetUpload() {
            // uploading shouldn't be this manual
            if (uploadCommandList.State == CommandListState::FINISHED)
                uploadCommandList.reset();
        }

        inline void executeUploads() {
            uploadCommandList.finish();
            uploadCommandList.wait();
        }
    };
}