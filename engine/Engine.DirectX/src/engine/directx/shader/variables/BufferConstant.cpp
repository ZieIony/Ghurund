#include "ghedxpch.h"
#include "BufferConstant.h"

namespace Ghurund::Engine::DirectX {
	DxBufferConstantInfo::DxBufferConstantInfo(
		const AString& name,
		uint32_t bindPoint,
		D3D12_SHADER_VISIBILITY visibility
	):ShaderConstant(name, bindPoint, visibility) {
	}

	void DxBufferConstantInfo::init(
		ID3D12ShaderReflectionConstantBuffer& constantBuffer,
		D3D12_SHADER_BUFFER_DESC& bufferDesc
	) {
		size = bufferDesc.Size;
		for (size_t i = 0; i < bufferDesc.Variables; i++) {
			ID3D12ShaderReflectionVariable* variable = constantBuffer.GetVariableByIndex(i);
			D3D12_SHADER_VARIABLE_DESC variableDesc;
			variable->GetDesc(&variableDesc);

			if (!(variableDesc.uFlags & D3D10_SVF_USED))
				continue;
			if (fields.any([&](auto& item) { return item.name == variableDesc.Name; }))
				continue;

			ID3D12ShaderReflectionType* variableType = variable->GetType();
			D3D12_SHADER_TYPE_DESC typeDesc;
			variableType->GetDesc(&typeDesc);

			fields.add({ typeDesc.Class, typeDesc.Type, variableDesc.Name, variableDesc.Size, variableDesc.StartOffset, variableDesc.DefaultValue });
		}
	}
}