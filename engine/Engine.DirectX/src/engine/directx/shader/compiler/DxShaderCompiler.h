#pragma once

#include "CompilationTarget.h"
#include "CompilerIncludeFXC.h"
#include "CompilerIncludeDXC.h"
#include "DxShaderProgram.h"

#include "core/IUnknownImpl.h"
#include "core/string/String.h"
#include "engine/directx/shader/DxShaderSource.h"
#include "engine/directx/shader/DxShaderType.h"
#include "engine/directx/shader/variables/DxSamplerInfo.h"
#include "engine/directx/shader/variables/DxTextureConstantInfo.h"
#include "engine/graphics/mesh/VertexStream.h"
#include "engine/directx/compute/DxComputeShader.h"
#include "engine/directx/rendering/DxGraphicsShader.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxGraphics;

	class DxShaderCompiler {
	private:
		DxGraphics& graphics;
		ResourceManager& resourceManager;
		IGPUMemoryManager& memoryManager;
		const CompilationTarget& target;

		Array<ShaderInputSemanticEnum> makeLayout(const D3D12_INPUT_LAYOUT_DESC& desc);
			
		DXGI_FORMAT getFormat(BYTE mask, D3D_REGISTER_COMPONENT_TYPE componentType);

		AString makeCompilationTarget(const DxShaderType& shaderType) const;

		D3D12_CULL_MODE convertCullMode(CullMode mode) const;

		D3D12_COMPARISON_FUNC convertDepthFunc(ComparisonFunc func) const;

		DxShaderProgram* compileFXC(const DxShaderProgramSourceCode& shaderSource, CompilerIncludeFXC& include, bool debug);

		DxShaderProgram* compileDXC(const DxShaderProgramSourceCode& shaderSource, CompilerIncludeDXC& include, bool debug);

	public:
		DxShaderCompiler(
			DxGraphics& graphics,
			ResourceManager& resourceManager,
			IGPUMemoryManager& memoryManager,
			const CompilationTarget& target = CompilationTarget::SHADER_5_0
		):graphics(graphics), resourceManager(resourceManager), memoryManager(memoryManager), target(target) {
		}

		void init();

		D3D12_INPUT_LAYOUT_DESC getInputLayout(const DxShaderProgram& program);

		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> makeGraphicsPipelineState(
			const Array<SharedPointer<DxShaderProgram>>& programs,
			D3D12_INPUT_LAYOUT_DESC inputLayout,
			ID3D12RootSignature* rootSignature
		);

		OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> makeComputePipelineState(
			const DxShaderProgram& computeProgram,
			ID3D12RootSignature* rootSignature
		);

		OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> makeRootSignature(
			const List<DxBufferConstantInfo*>& constantBuffers,
			const List<DxTextureConstantInfo*>& textures,
			const List<DxBufferConstantInfo*>& srvs,
			const List<DxTextureConstantInfo*>& uavs,
			const List<DxSamplerInfo*>& samplers
		);

		void initConstants(
			const DxShaderProgram& program,
			const List<SamplerInfo>& samplerInfos,
			List<DxBufferConstantInfo*>& constantBuffers,
			List<DxTextureConstantInfo*>& textures,
			List<DxBufferConstantInfo*>& srvs,
			List<DxTextureConstantInfo*>& uavs,
			List<DxSamplerInfo*>& samplers
		);

		DxShaderProgram* compile(const DxShaderProgramSourceCode& shaderSource, const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(), const List<DirectoryPath>* includeDirs = nullptr, bool debug =
#ifdef _DEBUG
			true
#else
			false
#endif
		);

		void build(
			DxGraphicsShader& shader,
			const List<SharedPointer<DxShaderProgram>>& programs
		);

		void build(
			DxComputeShader& shader,
			const DxShaderProgram& computeProgram
		);
	};
}
