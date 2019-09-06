#include "CommandList.h"
#include "graphics/shader/Shader.h"

namespace Ghurund {
	CommandList::~CommandList() {
        if(state==CommandListState::RECORDING)
            finish();
        if(state==CommandListState::CLOSED)
            wait();
        if(pipelineState!=nullptr)
            pipelineState->Release();
        if(rootSignature!=nullptr)
            rootSignature->Release();
        commandQueue->Release();
    }

    Status CommandList::init(Graphics & graphics, ID3D12CommandQueue *queue) {
        queue->AddRef();
        commandQueue = queue;

        Status result = fence.init(graphics.Device);
        if(result!=Status::OK)
            return result;

        if(FAILED(graphics.Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateCommandAllocator() failed\n"));

        if(FAILED(graphics.Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateCommandList() failed\n"));

        if(FAILED(commandList->Close()))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("commandList->Close() failed\n"));

        state = CommandListState::FINISHED;

        return Status::OK;
    }

    Status CommandList::wait() {
        if(state!=CommandListState::CLOSED)
            return Status::INV_STATE;
        Status result = fence.wait(commandQueue);
        rootSignature = nullptr;
        pipelineState = nullptr;
        for(size_t i = 0; i<resourceRefs.Size; i++)
            resourceRefs[i]->Release();
        resourceRefs.clear();
        pointerRefs.clear();
        state = CommandListState::FINISHED;
        return result;
    }

    Status CommandList::reset() {
        if(state!=CommandListState::FINISHED)
            return Status::INV_STATE;

        if(FAILED(commandAllocator->Reset()))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("commandAllocator->Reset() failed\n"));

        if(FAILED(commandList->Reset(commandAllocator.Get(), nullptr)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("commandList->Reset() failed\n"));

        state = CommandListState::RECORDING;

        return Status::OK;
    }

    Status CommandList::finish() {
        if(state!=CommandListState::RECORDING)
            return Status::INV_STATE;

        if(FAILED(commandList->Close()))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("commandList->Close() failed\n"));

        ID3D12CommandList* ppCommandLists[] = {commandList.Get()};
        commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

        fence.signal(commandQueue);

        state = CommandListState::CLOSED;

        return Status::OK;
    }

    bool CommandList::setPipelineState(ID3D12PipelineState *pipelineState) {
#ifdef _DEBUG
        if(pipelineState==nullptr)
            Logger::log(LogType::WARNING, _T("pipelineState cannot be null\n"));
#endif
        if(this->pipelineState!=pipelineState) {
            addResourceRef(pipelineState);
            commandList.Get()->SetPipelineState(pipelineState);
            this->pipelineState = pipelineState;
            return true;
        }
        return false;
    }

    bool CommandList::setGraphicsRootSignature(ID3D12RootSignature *rootSignature) {
#ifdef _DEBUG
        if(rootSignature==nullptr)
            Logger::log(LogType::WARNING, _T("rootSignature cannot be null\n"));
#endif
        if(this->rootSignature!=rootSignature) {
            addResourceRef(rootSignature);
            commandList.Get()->SetGraphicsRootSignature(rootSignature);
            this->rootSignature = rootSignature;
            return true;
        }
        return false;
    }

}