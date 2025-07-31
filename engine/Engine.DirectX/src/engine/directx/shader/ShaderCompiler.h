#pragma once

#include "CompilationTarget.h"
#include "CompilerInclude.h"
#include "Shader.h"
#include "ShaderType.h"
#include <core/io/DirectoryPath.h>
#include <core/string/String.h>
#include <engine/directx/Graphics.h>
#include <engine/parameter/ParameterManager.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	struct ShaderCompilationResult {
		Buffer data;
		AString logs;
		uint32_t errorCode;
	};

	class ShaderCompiler {
	private:
		const CompilationTarget& target;
		Graphics& graphics;
		ParameterManager& parameterManager;

		DXGI_FORMAT getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType);

		AString makeCompilationTarget(const ShaderType& shaderType) {
			const char* targetText = target.TargetName.Data;
			const char* typeText = shaderType.TypeName.Data;
			char text[10];
			sprintf_s(text, 10, "%s_%s", typeText, targetText);
			return text;
		}

		void initConstants(const ShaderProgram& program, NotNull<ShaderConstants> constants);

	public:
		ShaderCompiler(Graphics& graphics, ParameterManager& parameterManager, const CompilationTarget& target = CompilationTarget::SHADER_5_0):
			graphics(graphics), parameterManager(parameterManager), target(target) {
		}

		D3D12_INPUT_LAYOUT_DESC getInputLayout(const Buffer& byteCode);

		OwnedNotNull<ID3D12PipelineState> makePipelineState(const Array<SharedPointer<ShaderProgram>>& programs, ID3D12RootSignature* rootSignature, bool supportsTransparency);

		OwnedNotNull<ID3D12RootSignature> makeRootSignature(NotNull<ShaderConstants> constants);

		OwnedNotNull<ShaderConstants> makeConstants(const Array<SharedPointer<ShaderProgram>>& programs);

		ShaderProgram* compile(const AString& sourceCode, const ShaderType& shaderType, NotNull<CompilerInclude> include , bool debug =
#ifdef _DEBUG
			true
#else
			false
#endif
		);

		OwnedNotNull<Shader> build(const Array<SharedPointer<ShaderProgram>>& programs) {
			auto constants = makeConstants(programs);
			auto rootSignature = makeRootSignature(&constants);
			auto pipelineState = makePipelineState(programs, &rootSignature, false);
			Shader* shader = ghnew Shader();
			shader->init(std::move(rootSignature), std::move(pipelineState), std::move(constants));
			return shader;
		}
	};
}