#include "ghedxpch.h"
#include "DxComputeShader.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/shader/DxConstantsCollection.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxComputeShader::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<DxComputeShader>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxComputeShader>()
			.withSupertype(__super::GET_TYPE())
			.withConstructor(CONSTRUCTOR);

		return TYPE;
	}

	void DxComputeShader::finalize() {
		if (rootSignature != nullptr)
			rootSignature->Release();
		if (pipelineState != nullptr)
			pipelineState->Release();
	}

	void DxComputeShader::init(
		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> rootSignature,
		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> pipelineState,
		const List<DxBufferConstantInfo*>& bufferConstantInfos,
		const List<DxTextureConstantInfo*>& textureConstantInfos,
		const List<DxTextureConstantInfo*>& uavConstantInfos
	) {
		this->rootSignature = rootSignature.reset();
		this->pipelineState = pipelineState.reset();
		constants = [&] {
			auto c = ghnew DxConstantsCollection();
			c->init(bufferConstantInfos, textureConstantInfos, uavConstantInfos);
			return c;
		}();
	}

	DxComputeShader::~DxComputeShader() {
		finalize();
	}

	void DxComputeShader::invalidate() {
		__super::invalidate();

		finalize();

		rootSignature = nullptr;
		pipelineState = nullptr;
	}

	bool DxComputeShader::apply(DxComputeCommandList& commandList) {
		bool rsChanged = commandList.setRootSignature(rootSignature);
		bool psChanged = commandList.setPipelineState(pipelineState);

		((DxConstantsCollection*)constants)->apply(commandList);

		return rsChanged || psChanged;
	}
}
