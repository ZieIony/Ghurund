#pragma once

#include "DxComputeCommandList.h"

#include "engine/graphics/compute/ComputeShader.h"
#include "engine/directx/shader/variables/DxBufferConstantInfo.h"
#include <engine/directx/shader/variables/DxTextureConstantInfo.h>
#include <core/IUnknownImpl.h>
#include "core/object/OwnedNotNull.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxComputeShader:public ComputeShader {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = DxComputeShader::GET_TYPE();
#pragma endregion

	protected:
		ID3D12RootSignature* rootSignature = nullptr;
		ID3D12PipelineState* pipelineState = nullptr;

		void finalize();

		virtual bool getIsValidInternal() const override {
			return __super::getIsValidInternal() && pipelineState != nullptr && rootSignature != nullptr;
		}

		~DxComputeShader();

	public:
		void init(
			OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> rootSignature,
			OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> pipelineState,
			const List<DxBufferConstantInfo*>& bufferConstantInfos,
			const List<DxTextureConstantInfo*>& textureConstantInfos,
			const List<DxTextureConstantInfo*>& uavConstantInfos
		);

		bool apply(DxComputeCommandList& commandList);

		virtual void invalidate() override;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return DxComputeShader::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD, 1);
		static const inline ResourceFormat FORMAT_HLSL = ResourceFormat(L"hlsl", ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML, FORMAT_HLSL };
#pragma endregion
	};
}
