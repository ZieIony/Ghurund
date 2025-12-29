#pragma once

#include "CompilationTarget.h"
#include "CompilerInclude.h"
#include "DxShaderProgram.h"
#include "ShaderSettings.h"

#include "core/IUnknownImpl.h"
#include "core/string/String.h"
#include "engine/directx/shader/DxShader.h"
#include "engine/directx/shader/DxShaderType.h"
#include "engine/directx/shader/variables/ConstantBuffer.h"
#include "engine/directx/shader/variables/Sampler.h"
#include "engine/directx/shader/variables/TextureConstant.h"
#include "engine/graphics/mesh/VertexStream.h"

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

		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> makePipelineState(
			const Array<SharedPointer<DxShaderProgram>>& programs,
			D3D12_INPUT_LAYOUT_DESC inputLayout,
			ID3D12RootSignature* rootSignature,
			ShaderSettings shaderSettings
		);

		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> makeRootSignature(
			const List<ConstantBuffer*>& constantBuffers,
			const List<TextureConstant*>& textures,
			const List<Sampler*>& samplers
		);

		void initConstants(
			const DxShaderProgram& program,
			List<ConstantBuffer*>& constantBuffers,
			List<TextureConstant*>& textures,
			List<Sampler*>& samplers
		);

		DxShaderProgram* compile(const AString& sourceCode, const DxShaderType& shaderType, CompilerInclude* include = nullptr, bool debug =
#ifdef _DEBUG
			true
#else
			false
#endif
		);

		OwnedNotNull<DxShader, RefCountedObjectDeleter> build(
			const Array<SharedPointer<DxShaderProgram>>& programs,
			ShaderSettings shaderSettings
		);
	};
}