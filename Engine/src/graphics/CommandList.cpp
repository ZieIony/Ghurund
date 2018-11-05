#include "CommandList.h"
#include "graphics/shader/Shader.h"

namespace Ghurund {
    CommandList::~CommandList() {
        if(!closed)
            commandList->Close();
        if(commandQueue!=nullptr)
            fence.wait(commandQueue.Get());
    }

    Status CommandList::init(Graphics & graphics, ComPtr<ID3D12CommandQueue> &queue) {
        commandQueue = queue;

        Status result = fence.init(graphics.Device.Get());
        if(result!=Status::OK)
            return result;

        if(FAILED(graphics.Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)))) {
            Logger::log(_T("CreateCommandAllocator() failed\n"));
            return Status::CALL_FAIL;
        }

        if(FAILED(graphics.Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)))) {
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

    Status CommandList::wait() {
        if(!closed)
            return Status::INV_STATE;
        Status result = fence.wait(commandQueue.Get());
        resourceRefs.clear();
        pipelineState = nullptr;
        rootSignature = nullptr;
        return result;
    }

    Status CommandList::reset() {
        if(!closed)
            return Status::INV_STATE;

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

    Status CommandList::finish() {
        if(closed)
            return Status::INV_STATE;

        if(FAILED(commandList->Close())) {
            Logger::log(_T("commandList->Close() failed\n"));
            return Status::CALL_FAIL;
        }

        closed = true;

        ID3D12CommandList* ppCommandLists[] = {commandList.Get()};
        commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

        return Status::OK;
    }

    void CommandList::setPipelineState(ID3D12PipelineState *pipelineState) {
#ifdef _DEBUG
        if(pipelineState==nullptr)
            Logger::log(_T("pipelineState cannot be null\n"));
#endif
        if(this->pipelineState!=pipelineState) {
            this->pipelineState = pipelineState;
            commandList.Get()->SetPipelineState(pipelineState);
        }
    }

    void CommandList::setGraphicsRootSignature(ID3D12RootSignature * rootSignature) {
#ifdef _DEBUG
        if(pipelineState==nullptr)
            Logger::log(_T("rootSignature cannot be null\n"));
#endif
        if(this->rootSignature!=rootSignature) {
            this->rootSignature = rootSignature;
            commandList.Get()->SetGraphicsRootSignature(rootSignature);
        }
    }

    void CommandList::addResourceRef(Resource & resource) {
        resourceRefs.add(&resource);
    }

    bool CommandList::references(const Resource & resource) {
        return resourceRefs.contains((Resource*)&resource);
    }

}