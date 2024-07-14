#pragma once

#include "core/string/String.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund::Core::DirectX {
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class Fence {
    private:
        HANDLE fenceEvent = INVALID_HANDLE_VALUE;
        ComPtr<ID3D12Fence> fence;
        UINT64 fenceValue = 0;
        WString name;

    public:
        ~Fence() {
            if (fenceEvent != INVALID_HANDLE_VALUE)
                CloseHandle(fenceEvent);
        }

        void init(ID3D12Device* device);

        void signal(ID3D12CommandQueue* commandQueue);

        void wait(ID3D12CommandQueue* commandQueue);

        inline void setName(const WString& name) {
            this->name = name;
            fence->SetName(name.Data);
        }

        inline WString getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) WString Name;

        UINT64 getValue() {
            return fenceValue;
        }
    };
}