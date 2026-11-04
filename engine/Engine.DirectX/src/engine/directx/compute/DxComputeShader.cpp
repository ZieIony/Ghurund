#include "ghedxpch.h"
#include "DxComputeShader.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/shader/DxConstantCollection.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxComputeShader::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<DxComputeShader>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxComputeShader>()
			.withSupertype(__super::GET_TYPE())
			.withConstructor(CONSTRUCTOR);

		return TYPE;
	}

	void DxComputeShader::init(
		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> rootSignature,
		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> pipelineState,
		const List<DxBufferConstantInfo*>& bufferConstantInfos,
		const List<DxTextureConstantInfo*>& textureConstantInfos,
		const List<DxTextureConstantInfo*>& uavConstantInfos
	) {
		deinit();

		this->rootSignature = rootSignature.reset();
		this->pipelineState = pipelineState.reset();
		constants = [&] {
			auto c = ghnew DxConstantCollection();
			c->init(bufferConstantInfos, textureConstantInfos, uavConstantInfos);
			return c;
		}();

		State = ResourceState::INITIALIZED;
	}

	DxComputeShader::~DxComputeShader() {
		deinit_internal();
	}

	bool DxComputeShader::apply(DxComputeCommandList& commandList) {
		bool rsChanged = commandList.setRootSignature(rootSignature);
		bool psChanged = commandList.setPipelineState(pipelineState);

		((DxConstantCollection*)constants)->apply(commandList);

		return rsChanged || psChanged;
	}
}
