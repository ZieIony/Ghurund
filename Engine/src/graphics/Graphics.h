#pragma once

#include "Ghurund.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include "collection/List.h"
#include "core/Logger.h"
#include "Adapter.h"

#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    class Graphics {
    private:
        ComPtr<ID3D12Device> device;
        ComPtr<ID3D12CommandQueue> commandQueue;
        ComPtr<IDXGIFactory4> factory;

        List<Adapter*> adapters;

        Status initAdapters() {
            ComPtr<IDXGIAdapter1> adapter;

            unsigned int adapterIndex = 0;
            while(true){
                if(DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
                    break;

                adapters.add(ghnew Adapter(adapter));
                adapterIndex++;
            }

            if(FAILED(factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)))) {
                Logger::log(_T("factory->EnumWarpAdapter() failed\n"));
                return Status::CALL_FAIL;
            }

            adapters.add(ghnew Adapter(adapter));

            return adapters.Size>0 ? Status::OK : Status::DIRECTX12_NOT_SUPPORTED;
        }

    public:

        ~Graphics() {
            for(unsigned int i = 0; i<adapters.Size; i++)
                delete adapters[i];
        }

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

        List<Adapter*> &getAdapters() {
            return adapters;
        }
    };
}