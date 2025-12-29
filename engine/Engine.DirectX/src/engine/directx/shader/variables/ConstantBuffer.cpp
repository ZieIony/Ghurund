#include "ghedxpch.h"
#include "ConstantBuffer.h"

namespace Ghurund::Engine::DirectX {
	ConstantBuffer::ConstantBuffer(
		const AString& name,
		uint32_t bindPoint,
		D3D12_SHADER_VISIBILITY visibility
	):ShaderConstant(name, bindPoint, visibility) {
	}

	void ConstantBuffer::init(
		DxGraphics& graphics,
		D3D12_SHADER_BUFFER_DESC& bufferDesc
	) {
		buffer.init(graphics, bufferDesc.Size);
	}

	void ConstantBuffer::initVariables(
		ID3D12ShaderReflectionConstantBuffer* constantBuffer,
		D3D12_SHADER_BUFFER_DESC& bufferDesc
	) {
		for (size_t i = 0; i < bufferDesc.Variables; i++) {
			ID3D12ShaderReflectionVariable* variable = constantBuffer->GetVariableByIndex(i);
			D3D12_SHADER_VARIABLE_DESC variableDesc;
			variable->GetDesc(&variableDesc);

			if (!(variableDesc.uFlags & D3D10_SVF_USED))
				continue;
			if (variables.any([&](auto& item) {return item.name == variableDesc.Name; }))
				continue;

			ID3D12ShaderReflectionType* variableType = variable->GetType();
			D3D12_SHADER_TYPE_DESC typeDesc;
			variableType->GetDesc(&typeDesc);

			variables.add({ typeDesc.Class, typeDesc.Type, variableDesc.Name, variableDesc.Size, variableDesc.StartOffset, variableDesc.DefaultValue });
		}
	}
}