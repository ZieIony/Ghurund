#pragma once

#include "DxGraphicsCommandList.h"

#include "core/collection/Array.h"
#include "core/collection/List.h"
#include "core/IUnknownImpl.h"
#include "core/object/OwnedNotNull.h"
#include "engine/graphics/mesh/VertexStream.h"
#include "engine/graphics/rendering/GraphicsShader.h"
#include "engine/directx/shader/variables/DxBufferConstantInfo.h"
#include "engine/directx/shader/variables/DxTextureConstantInfo.h"

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;
	using namespace Microsoft::WRL;

	class DxGraphicsShader:public GraphicsShader {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = DxGraphicsShader::GET_TYPE();
#pragma endregion

	private:
		Array<VertexRole> layout;
		ID3D12RootSignature* rootSignature = nullptr;
		ID3D12PipelineState* pipelineState = nullptr;

		void finalize();

	protected:
		virtual bool getIsValidInternal() const override {
			return __super::getIsValidInternal() && pipelineState != nullptr && rootSignature != nullptr;
		}

		~DxGraphicsShader();

	public:
		DxGraphicsShader() {}

		inline const Array<VertexRole>& getLayout() const {
			return layout;
		}

		__declspec(property(get = getLayout)) const Array<VertexRole>& Layout;
		
		void init(
			const Array<VertexRole>& layout,
			OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> rootSignature,
			OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> pipelineState,
			const List<DxBufferConstantInfo*>& bufferConstantInfos,
			const List<DxTextureConstantInfo*>& textureConstantInfos,
			const List<DxTextureConstantInfo*>& uavConstantInfos,
			bool isTransparencyEnabled
		);

		bool apply(DxGraphicsCommandList& commandList);

		virtual void invalidate() override;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return DxGraphicsShader::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_SHADER = ResourceFormat(L"shader", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_HLSL = ResourceFormat(L"hlsl", ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SHADER, FORMAT_HLSL };

		static const inline uint32_t VERSION = 1;
#pragma endregion
	};
}
