#pragma once

#include "CompilationTarget.h"
#include "CompilerInclude.h"
#include "DxShaderProgram.h"

#include "core/IUnknownImpl.h"
#include "core/string/String.h"
#include "engine/directx/shader/DxShaderSource.h"
#include "engine/directx/shader/DxShaderType.h"
#include "engine/directx/shader/variables/DxSamplerInfo.h"
#include "engine/directx/shader/variables/DxTextureConstantInfo.h"
#include "engine/graphics/mesh/VertexStream.h"
#include <engine/directx/compute/DxComputeShader.h>
#include <engine/directx/rendering/DxGraphicsShader.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxGraphics;

	class DxShaderCompiler {
	private:
		const CompilationTarget& target;
		DxGraphics& graphics;

		Array<VertexRole> makeLayout(const D3D12_INPUT_LAYOUT_DESC& desc);
			
		DXGI_FORMAT getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType);

		AString makeCompilationTarget(const DxShaderType& shaderType) {
			const char* targetText = target.TargetName.Data;
			const char* typeText = shaderType.TypeName.Data;
			char text[10];
			sprintf_s(text, 10, "%s_%s", typeText, targetText);
			return text;
		}

	public:
		DxShaderCompiler(DxGraphics& graphics, const CompilationTarget& target = CompilationTarget::SHADER_5_0):graphics(graphics), target(target) {}

		D3D12_INPUT_LAYOUT_DESC getInputLayout(const Buffer& byteCode);

		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> makeGraphicsPipelineState(
			const Array<SharedPointer<DxShaderProgram>>& programs,
			D3D12_INPUT_LAYOUT_DESC inputLayout,
			ID3D12RootSignature* rootSignature,
			ShaderSettings shaderSettings
		);

		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> makeComputePipelineState(
			const DxShaderProgram& computeProgram,
			ID3D12RootSignature* rootSignature
		);

		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> makeRootSignature(
			const List<DxBufferConstantInfo*>& constantBuffers,
			const List<DxTextureConstantInfo*>& textures,
			const List<DxTextureConstantInfo*>& uavs,
			const List<DxSamplerInfo*>& samplers
		);

		void initConstants(
			const DxShaderProgram& program,
			const List<SamplerInfo>& samplerInfos,
			List<DxBufferConstantInfo*>& constantBuffers,
			List<DxTextureConstantInfo*>& textures,
			List<DxTextureConstantInfo*>& uavs,
			List<DxSamplerInfo*>& samplers
		);

		DxShaderProgram* compile(const DxShaderProgramSourceCode& shaderSource, CompilerInclude* include = nullptr, bool debug =
#ifdef _DEBUG
			true
#else
			false
#endif
		);

		void build(
			DxGraphicsShader& shader,
			const Array<SharedPointer<DxShaderProgram>>& programs,
			const List<SamplerInfo>& samplerInfos,
			ShaderSettings shaderSettings
		);

		void build(
			DxComputeShader& shader,
			const DxShaderProgram& computeProgram,
			const List<SamplerInfo>& samplerInfos
		);
	};
}
