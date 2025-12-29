#pragma once

#include "ShaderConstant.h"

#include <d3dcompiler.h>

namespace Ghurund::Engine::DirectX {
	class TextureBufferConstant:public ShaderConstant {
	public:
		TextureBufferConstant(
			ID3D12ShaderReflectionConstantBuffer* constantBuffer,
			D3D12_SHADER_BUFFER_DESC& bufferDesc,
			unsigned int bindPoint,
			D3D12_SHADER_VISIBILITY visibility
		):ShaderConstant(bufferDesc.Name, bindPoint, visibility) {
		}
	};
}