#include "ghcdxpch.h"
#include "CommandList.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core::DirectX {
	const Ghurund::Core::Type& CommandList::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<CommandList>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<CommandList>(Ghurund::Core::DirectX::NAMESPACE_NAME, GH_STRINGIFY(CommandList))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	CommandList::~CommandList() {
		if (state == CommandListState::RECORDING) {
			commandList->OMSetRenderTargets(0, 0, true, 0);
			finish();
		}
		if (state == CommandListState::CLOSED)
			wait();

		// https://github.com/Microsoft/DirectX-Graphics-Samples/issues/261
		fence.signal(commandQueue);
		fence.wait(commandQueue);

		if (pipelineState != nullptr)
			pipelineState->Release();
		if (rootSignature != nullptr)
			rootSignature->Release();
		commandQueue->Release();
	}

	void CommandList::init(Graphics& graphics, ID3D12CommandQueue* queue) {
		queue->AddRef();
		commandQueue = queue;

		fence.init(graphics.Device);

		if (FAILED(graphics.Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)))) {
			Logger::log(LogType::ERR0R, _T("CreateCommandAllocator() failed\n"));
			throw CallFailedException();
		}

		if (FAILED(graphics.Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)))) {
			Logger::log(LogType::ERR0R, _T("CreateCommandList() failed\n"));
			throw CallFailedException();
		}

#ifdef _DEBUG
		Name = L"unnamed CommandList";
#endif

		if (FAILED(commandList->Close())) {
			Logger::log(LogType::ERR0R, _T("commandList->Close() failed\n"));
			throw CallFailedException();
		}

		state = CommandListState::FINISHED;
	}

	void CommandList::wait() {
		if (state != CommandListState::CLOSED)
			throw InvalidStateException();

		fence.wait(commandQueue);
		rootSignature = nullptr;
		pipelineState = nullptr;
		for (size_t i = 0; i < resourceRefs.Size; i++)
			resourceRefs[i]->Release();
		resourceRefs.clear();
		pointerRefs.clear();
		state = CommandListState::FINISHED;
	}

	void CommandList::reset() {
		if (state != CommandListState::FINISHED)
			throw InvalidStateException();

		if (FAILED(commandAllocator->Reset())) {
			Logger::log(LogType::ERR0R, _T("commandAllocator->Reset() failed\n"));
			throw CallFailedException();
		}

		if (FAILED(commandList->Reset(commandAllocator.Get(), nullptr))) {
			Logger::log(LogType::ERR0R, _T("commandList->Reset() failed\n"));
			throw CallFailedException();
		}

		state = CommandListState::RECORDING;
	}

	void CommandList::finish() {
		if (state != CommandListState::RECORDING)
			throw InvalidStateException();

		if (FAILED(commandList->Close())) {
			Logger::log(LogType::ERR0R, _T("commandList->Close() failed\n"));
			throw CallFailedException();
		}

		ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		fence.signal(commandQueue);

		state = CommandListState::CLOSED;
	}

	bool CommandList::setPipelineState(ID3D12PipelineState* pipelineState) {
#ifdef _DEBUG
		if (pipelineState == nullptr)
			Logger::log(LogType::WARNING, _T("pipelineState cannot be null\n"));
#endif
		if (this->pipelineState != pipelineState) {
			addResourceRef(pipelineState);
			commandList.Get()->SetPipelineState(pipelineState);
			this->pipelineState = pipelineState;
			return true;
		}
		return false;
	}

	bool CommandList::setGraphicsRootSignature(ID3D12RootSignature* rootSignature) {
#ifdef _DEBUG
		if (rootSignature == nullptr)
			Logger::log(LogType::WARNING, _T("rootSignature cannot be null\n"));
#endif
		if (this->rootSignature != rootSignature) {
			addResourceRef(rootSignature);
			commandList.Get()->SetGraphicsRootSignature(rootSignature);
			this->rootSignature = rootSignature;
			return true;
		}
		return false;
	}

}