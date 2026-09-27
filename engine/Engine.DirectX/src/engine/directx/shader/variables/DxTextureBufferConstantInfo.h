#pragma once

#include "DxShaderConstantInfo.h"

#include <d3dcompiler.h>

namespace Ghurund::Engine::DirectX {
	class DxTextureBufferConstantInfo:public DxShaderConstantInfo {
	public:
		DxTextureBufferConstantInfo(
			ID3D12ShaderReflectionConstantBuffer* constantBuffer,
			D3D12_SHADER_BUFFER_DESC& bufferDesc,
			unsigned int bindPoint,
			D3D12_SHADER_VISIBILITY visibility
		):DxShaderConstantInfo(bufferDesc.Name, bindPoint, visibility) {
		}
	};
}
