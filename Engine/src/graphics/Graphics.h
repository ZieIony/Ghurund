#pragma once

#include "Ghurund.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    class Graphics {
    private:
        ComPtr<ID3D12Device> device;
        ComPtr<ID3D12CommandQueue> commandQueue;
        ComPtr<IDXGIFactory4> factory;

        bool software = false;
        
    public:

        Status init();

        ComPtr<ID3D12Device> &getDevice() {
            return device;
        }

        ComPtr<ID3D12CommandQueue> &getCommandQueue() {
            return commandQueue;
        }

        ComPtr<IDXGIFactory4> &getFactory() {
            return factory;
        }
    };
}