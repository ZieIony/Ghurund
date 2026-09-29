#include "ghedxpch.h"
#include "DxComputeCommandList.h"

#include "engine/directx/DxGraphics.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxComputeCommandList::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxComputeCommandList>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void DxComputeCommandList::init(DxGraphics& graphics, NotNull<ID3D12CommandQueue> queue) {
		queue->AddRef();
		commandQueue = &queue;

		fence.init(graphics.Device);

		if (FAILED(graphics.Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COMPUTE, IID_PPV_ARGS(&commandAllocator)))) {
			Logger::log(LogType::ERR0R, _T("CreateCommandAllocator() failed\n"));
			throw CallFailedException();
		}

		// TODO: D3D12_COMMAND_LIST_TYPE_COPY
		if (FAILED(graphics.Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_COMPUTE, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)))) {
			Logger::log(LogType::ERR0R, _T("CreateCommandList() failed\n"));
			throw CallFailedException();
		}

#ifdef _DEBUG
		Name = L"unnamed ComputeCommandList";
#endif

		if (FAILED(commandList->Close())) {
			Logger::log(LogType::ERR0R, _T("commandList->Close() failed\n"));
			throw CallFailedException();
		}

		state = CommandListState::FINISHED;
	}

	bool DxComputeCommandList::setRootSignature(ID3D12RootSignature* rootSignature) {
#ifdef _DEBUG
		if (rootSignature == nullptr)
			Logger::log(LogType::WARNING, _T("rootSignature cannot be null\n"));
#endif
		if (this->rootSignature != rootSignature) {
			addResourceRef(rootSignature);
			commandList.Get()->SetComputeRootSignature(rootSignature);
			this->rootSignature = rootSignature;
			return true;
		}
		return false;
	}
}
