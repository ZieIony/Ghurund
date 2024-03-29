#pragma once

#include "core/directx/CommandList.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund::Core::DirectX {
    class DepthBuffer {
    private:
        ComPtr<ID3D12DescriptorHeap> dsvHeap;
        ComPtr<ID3D12Resource> depthStencil;
        D3D12_CPU_DESCRIPTOR_HANDLE handle;

    public:
        Status init(Graphics& graphics, unsigned int width, unsigned int height);

        void clear(CommandList &commandList) {
            commandList.get()->ClearDepthStencilView(handle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
        }

        inline D3D12_CPU_DESCRIPTOR_HANDLE &getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) D3D12_CPU_DESCRIPTOR_HANDLE& Handle;
    };
}