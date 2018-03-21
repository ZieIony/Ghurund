#pragma once

#include "application/Window.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    class Fence {
    private:
        HANDLE fenceEvent = INVALID_HANDLE_VALUE;
        ComPtr<ID3D12Fence> fence;
        UINT64 fenceValue = 0;

    public:
        ~Fence() {
            if(fenceEvent!=INVALID_HANDLE_VALUE)
                CloseHandle(fenceEvent);
        }

        Status init(ID3D12Device *device);

        Status wait(ID3D12CommandQueue *commandQueue);
    };
}