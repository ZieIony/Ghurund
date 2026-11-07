#include "ghedxpch.h"
#include "DxGraphicsShader.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/shader/DxConstantCollection.h"

namespace Ghurund::Engine::DirectX {

	const Ghurund::Core::Type& DxGraphicsShader::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<DxGraphicsShader>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphicsShader>()
			.withSupertype(__super::GET_TYPE())
			.withConstructor(CONSTRUCTOR);

		return TYPE;
	}

	void DxGraphicsShader::init(
		NotNull<IGPUMemoryManager> memoryManager,
		const Array<VertexRole>& layout,
		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> rootSignature,
		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> pipelineState,
		const List<DxBufferConstantInfo*>& bufferConstantInfos,
		const List<DxTextureConstantInfo*>& textureConstantInfos,
		const List<DxTextureConstantInfo*>& uavConstantInfos,
		bool isTransparencyEnabled
	) {
		deinit();

		this->layout = layout;
		this->rootSignature = rootSignature.reset();
		this->pipelineState = pipelineState.reset();
		constants = [&] {
			auto c = ghnew DxConstantCollection();
			c->init(bufferConstantInfos, textureConstantInfos, uavConstantInfos);
			return c;
		}();
		this->isTransparencyEnabled = isTransparencyEnabled;

		dataSize.system = sizeof(*this) + source->getDataSize();

		__super::init(memoryManager);

		State = ResourceState::INITIALIZED;
	}

	bool DxGraphicsShader::apply(DxGraphicsCommandList& commandList) {
		bool rsChanged = commandList.setRootSignature(rootSignature);
		bool psChanged = commandList.setPipelineState(pipelineState);

		((DxConstantCollection*)constants)->apply(commandList);

		return rsChanged || psChanged;
	}

	DxGraphicsShader::~DxGraphicsShader() {
		deinit_internal();
	}
}
