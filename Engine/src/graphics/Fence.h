#pragma once

#include "application/Window.h"
#include "core/NamedObject.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund {
    using namespace Microsoft::WRL;

    class Fence: public NamedObject {
    private:
        HANDLE fenceEvent = INVALID_HANDLE_VALUE;
        ComPtr<ID3D12Fence> fence;
        UINT64 fenceValue = 0;

    public:
        Fence() {
#ifdef _DEBUG
            Name = _T("unnamed Fence");
#endif
        }

        ~Fence() {
            if (fenceEvent != INVALID_HANDLE_VALUE)
                CloseHandle(fenceEvent);
        }

        Status init(ID3D12Device* device);

        Status signal(ID3D12CommandQueue* commandQueue);

        Status wait(ID3D12CommandQueue* commandQueue);

        virtual void setName(const UnicodeString& name) override {
            NamedObject::setName(name);
            fence->SetName(name.getData());
        }

        UINT64 getValue() {
            return fenceValue;
        }
    };
}