#pragma once

#include "CompilationTarget.h"
#include "CompilerInclude.h"
#include "DxShader.h"
#include "DxShaderType.h"
#include <core/io/DirectoryPath.h>
#include <core/string/String.h>
#include <engine/directx/DxGraphics.h>
#include <engine/parameter/ParameterManager.h>
#include "core/IUnknownImpl.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	struct ShaderCompilationResult {
		Buffer data;
		AString logs;
		uint32_t errorCode;
	};

	class DxShaderCompiler {
	private:
		const CompilationTarget& target;
		DxGraphics& graphics;

		DXGI_FORMAT getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType);

		AString makeCompilationTarget(const DxShaderType& shaderType) {
			const char* targetText = target.TargetName.Data;
			const char* typeText = shaderType.TypeName.Data;
			char text[10];
			sprintf_s(text, 10, "%s_%s", typeText, targetText);
			return text;
		}

		void initConstants(const DxShaderProgram& program, NotNull<ShaderConstants> constants);

	public:
		DxShaderCompiler(DxGraphics& graphics, const CompilationTarget& target = CompilationTarget::SHADER_5_0):graphics(graphics), target(target) {}

		D3D12_INPUT_LAYOUT_DESC getInputLayout(const Buffer& byteCode);

		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> makePipelineState(
			const Array<SharedPointer<DxShaderProgram>>& programs,
			ID3D12RootSignature* rootSignature,
			bool supportsTransparency
		);

		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> makeRootSignature(NotNull<ShaderConstants> constants);

		OwnedNotNull<ShaderConstants> makeConstants(const Array<SharedPointer<DxShaderProgram>>& programs);

		DxShaderProgram* compile(const AString& sourceCode, const DxShaderType& shaderType, CompilerInclude* include = nullptr, bool debug =
#ifdef _DEBUG
			true
#else
			false
#endif
		);

		OwnedNotNull<DxShader, RefCountedObjectDeleter> build(const Array<SharedPointer<DxShaderProgram>>& programs);
	};
}