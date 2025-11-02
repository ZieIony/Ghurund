#pragma once

#include "engine/directx/buffer/DynamicBuffer.h"
#include "engine/directx/shader/ConstantBufferField.h"
#include "engine/directx/shader/ShaderConstant.h"
#include "engine/parameter/ParameterProvider.h"

#include <d3dcompiler.h>

namespace Ghurund::Engine::DirectX {
	class ConstantBuffer:public ShaderConstant, public ParameterProvider {
	public:
		GPUBuffer buffer;
		List<ConstantBufferField*> variables;
#ifdef _DEBUG
		bool* reported;
#endif

		ConstantBuffer(
			DxGraphics& graphics,
			ID3D12ShaderReflectionConstantBuffer* constantBuffer,
			D3D12_SHADER_BUFFER_DESC& bufferDesc,
			uint32_t bindPoint,
			D3D12_SHADER_VISIBILITY visibility,
			ParameterManager& parameterManager
		);

		~ConstantBuffer() {
			variables.deleteItems();
#ifdef _DEBUG
			delete[] reported;
#endif
		}

		virtual void updateParameters() override;

		inline void set(DxGraphics& graphics, CommandList& commandList) {
			buffer.set(graphics, commandList, bindSlot);
		}
	};

}