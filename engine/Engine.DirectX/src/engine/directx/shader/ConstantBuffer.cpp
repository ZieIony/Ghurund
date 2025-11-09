#include "ghedxpch.h"
#include "ConstantBuffer.h"

#include <engine/parameter/Parameter.h>
#include "engine/directx/parameter/DxParameter.h"

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

	void ConstantBuffer::initParameters(
		ID3D12ShaderReflectionConstantBuffer* constantBuffer,
		D3D12_SHADER_BUFFER_DESC& bufferDesc
	) {
		for (size_t i = 0; i < bufferDesc.Variables; i++) {
			ID3D12ShaderReflectionVariable* variable = constantBuffer->GetVariableByIndex(i);
			D3D12_SHADER_VARIABLE_DESC variableDesc;
			variable->GetDesc(&variableDesc);

			if (!(variableDesc.uFlags & D3D10_SVF_USED))
				continue;
			if (variables.any([&](auto& item) {return item->name == variableDesc.Name; }))
				continue;

			variables.add(ghnew ConstantBufferField(variableDesc.Name, variableDesc.Size, variableDesc.StartOffset));

			ID3D12ShaderReflectionType* variableType = variable->GetType();
			D3D12_SHADER_TYPE_DESC typeDesc;
			variableType->GetDesc(&typeDesc);

			auto vp = makeDxParameterByType(typeDesc.Class, typeDesc.Type, variableDesc.Name, variableDesc.Size, variableDesc.DefaultValue);
			Parameters.put(vp);
			vp->release();
		}
	}
}