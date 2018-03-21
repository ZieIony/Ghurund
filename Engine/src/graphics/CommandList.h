#pragma once

#include "Fence.h"
#include "core/Logger.h"
#include "Graphics.h"

namespace Ghurund {
    class CommandList {
    private:
        Fence fence;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandQueue> commandQueue;

    public:
        ~CommandList() {
            fence.wait(commandQueue.Get());
        }

        Status init(Graphics &graphics) {
            commandQueue = graphics.getCommandQueue();

            Status result = fence.init(graphics.getDevice().Get());
            if(result!=Status::OK)
                return result;

            if(FAILED(graphics.getDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
               IID_PPV_ARGS(&commandAllocator)))) {
                Logger::log(_T("CreateCommandAllocator() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(graphics.getDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
               commandAllocator.Get(), nullptr,
               IID_PPV_ARGS(&commandList)))) {
                Logger::log(_T("CreateCommandList() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(commandList->Close())) {
                Logger::log(_T("commandList->Close() failed\n"));
                return Status::CALL_FAIL;
            }

            return Status::OK;
        }

        Status wait() {
            return fence.wait(commandQueue.Get());
        }

        Status reset() {
            if(FAILED(commandAllocator->Reset())) {
                Logger::log(_T("commandAllocator->Reset() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(commandList->Reset(commandAllocator.Get(), nullptr))) {
                Logger::log(_T("commandList->Reset() failed\n"));
                return Status::CALL_FAIL;
            }

            return Status::OK;
        }

        Status finish() {
            if(FAILED(commandList->Close())) {
                Logger::log(_T("commandList->Close() failed\n"));
                return Status::CALL_FAIL;
            }

            ID3D12CommandList* ppCommandLists[] = {commandList.Get()};
            commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

            return Status::OK;
        }

        ID3D12GraphicsCommandList *get() {
            return commandList.Get();
        }
    };
}