#include "ghcdxpch.h"
#include "Fence.h"

#include "Graphics.h"
#include "core/logging/Logger.h"

namespace Ghurund::Core::DirectX {
    Status Fence::init(ID3D12Device *device) {
        if(FAILED(device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)))) {
            Logger::log(LogType::ERR0R, _T("device->CreateFence() failed\n"));
            return Status::CALL_FAIL;
        }
        fenceValue++;

        fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if(fenceEvent == nullptr) {
            if(FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
                Logger::log(LogType::ERR0R, _T("HRESULT_FROM_WIN32() failed\n"));
                return Status::CALL_FAIL;
            }
        }

        return Status::OK;
    }

    Status Fence::signal(ID3D12CommandQueue * commandQueue) {
        fenceValue++;
        if(FAILED(commandQueue->Signal(fence.Get(), fenceValue))) {
            Logger::log(LogType::ERR0R, _T("commandQueue->Signal() failed\n"));
            return Status::CALL_FAIL;
        }

        return Status::OK;
    }

    Status Fence::wait(ID3D12CommandQueue * commandQueue) {
        if(fence->GetCompletedValue() < fenceValue) {
            if(FAILED(fence->SetEventOnCompletion(fenceValue, fenceEvent))) {
                Logger::log(LogType::ERR0R, _T("fence->SetEventOnCompletion() failed\n"));
                return Status::CALL_FAIL;
            }
            WaitForSingleObject(fenceEvent, INFINITE);
        }

        return Status::OK;
    }
}