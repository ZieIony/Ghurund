#pragma once

#include "Fence.h"
#include "core/Logger.h"
#include "Graphics.h"
#include "core/NamedObject.h"

namespace Ghurund {
    class CommandList: public NamedObject {
    private:
        Fence fence;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ComPtr<ID3D12CommandQueue> commandQueue;
        bool closed;

    public:
        CommandList() {
#ifdef _DEBUG
            Name = _T("unnamed CommandList");
#endif
        }

        ~CommandList() {
            if(commandQueue!=nullptr)
                fence.wait(commandQueue.Get());
        }

        Status init(Graphics &graphics) {
            commandQueue = graphics.CommandQueue;

            Status result = fence.init(graphics.Device.Get());
            if(result!=Status::OK)
                return result;

            if(FAILED(graphics.Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,IID_PPV_ARGS(&commandAllocator)))) {
                Logger::log(_T("CreateCommandAllocator() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(graphics.Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,commandAllocator.Get(), nullptr,IID_PPV_ARGS(&commandList)))) {
                Logger::log(_T("CreateCommandList() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(commandList->Close())) {
                Logger::log(_T("commandList->Close() failed\n"));
                return Status::CALL_FAIL;
            }

            closed = true;

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

            closed = false;

            return Status::OK;
        }

        Status finish() {
            if(FAILED(commandList->Close())) {
                Logger::log(_T("commandList->Close() failed\n"));
                return Status::CALL_FAIL;
            }

            closed = true;

            ID3D12CommandList* ppCommandLists[] = {commandList.Get()};
            commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

            return Status::OK;
        }

        ID3D12GraphicsCommandList *get() {
            return commandList.Get();
        }

        bool isClosed() {
            return closed;
        }

        __declspec(property(get = isClosed)) bool Closed;

        virtual void setName(const String &name) override {
            NamedObject::setName(name);
            commandList->SetName(name.getData());
        }
    };
}