#pragma once

#include "Status.h"
#include "core/NamedObject.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund::Core::DirectX {
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class Fence: public NamedObject<wchar_t> {
    private:
        HANDLE fenceEvent = INVALID_HANDLE_VALUE;
        ComPtr<ID3D12Fence> fence;
        UINT64 fenceValue = 0;

    public:
        Fence() {
#ifdef _DEBUG
            Name = L"unnamed Fence";
#endif
        }

        ~Fence() {
            if (fenceEvent != INVALID_HANDLE_VALUE)
                CloseHandle(fenceEvent);
        }

        Status init(ID3D12Device* device);

        Status signal(ID3D12CommandQueue* commandQueue);

        Status wait(ID3D12CommandQueue* commandQueue);

        virtual void setName(const WString& name) override {
            NamedObject::setName(name);
            fence->SetName(name.Data);
        }

        UINT64 getValue() {
            return fenceValue;
        }
    };
}