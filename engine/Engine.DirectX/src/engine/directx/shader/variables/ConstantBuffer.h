#pragma once

#include "ConstantBufferField.h"
#include "ShaderConstant.h"

#include "engine/directx/buffer/GPUBuffer.h"

#include <d3dcompiler.h>

namespace Ghurund::Engine::DirectX {
	class ConstantBuffer:public ShaderConstant {
	private:
		GPUBuffer buffer;
		List<ConstantBufferField> variables;

		ConstantBuffer(const ConstantBuffer& other) = delete;

	public:
		ConstantBuffer(
			const AString& name,
			uint32_t bindPoint,
			D3D12_SHADER_VISIBILITY visibility
		);

		void init(DxGraphics& graphics, D3D12_SHADER_BUFFER_DESC& bufferDesc);

		void initVariables(ID3D12ShaderReflectionConstantBuffer* constantBuffer, D3D12_SHADER_BUFFER_DESC& bufferDesc);

		inline const List<ConstantBufferField>& getVariables() const {
			return variables;
		}

		__declspec(property(get = getVariables)) const List<ConstantBufferField>& Variables;

		inline void setValue(const void* value, size_t size, size_t offset) {
			buffer.setValue(value, size, offset);
		}

		inline void set(CommandList& commandList) {
			buffer.set(commandList, bindSlot);
		}
	};
}