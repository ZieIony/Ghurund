#include "ghedxpch.h"
#include "DxGraphicsCommandList.h"

#include "engine/directx/DxGraphics.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxGraphicsCommandList::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphicsCommandList>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	DxGraphicsCommandList::~DxGraphicsCommandList() {
		if (state == CommandListState::RECORDING)
			commandList->OMSetRenderTargets(0, 0, true, 0);
	}

	void DxGraphicsCommandList::init(DxGraphics& graphics, NotNull<ID3D12CommandQueue> queue) {
		queue->AddRef();
		commandQueue = &queue;

		fence.init(graphics.Device);

		if (FAILED(graphics.Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)))) {
			Logger::log(LogType::ERR0R, _T("CreateCommandAllocator() failed\n"));
			throw CallFailedException();
		}

		// TODO: D3D12_COMMAND_LIST_TYPE_COPY
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

	bool DxGraphicsCommandList::setRootSignature(ID3D12RootSignature* rootSignature) {
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
