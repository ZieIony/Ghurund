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

		ConstantBuffer(
			const AString& name,
			uint32_t bindPoint,
			D3D12_SHADER_VISIBILITY visibility
		);

		~ConstantBuffer() {
			variables.deleteItems();
		}

		void init(DxGraphics& graphics, D3D12_SHADER_BUFFER_DESC& bufferDesc);

		void initParameters(ID3D12ShaderReflectionConstantBuffer* constantBuffer, D3D12_SHADER_BUFFER_DESC& bufferDesc);

		inline void set(DxGraphics& graphics, CommandList& commandList, ParameterManager& parameterManager) {
			size_t i = 0;
			auto it = parameters.begin();
			while (i < variables.Size) {
				Parameter* p = it->get();
				if (p->IsEmpty)
					p = parameterManager.Parameters.get(p->Name);
				ConstantBufferField* v = variables[i];
				buffer.setValue(p->RawValue, v->size, v->offset);
				i++;
				it++;
			}
			buffer.set(graphics, commandList, bindSlot);
		}
	};

}