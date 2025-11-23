#include "ghedxpch.h"
#include "ConstantBuffer.h"

#include <engine/parameter/Parameter.h>
#include "engine/directx/parameter/DxParameter.h"
#include "core/logging/Logger.h"

#include <format>

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
	
	void ConstantBuffer::set(CommandList& commandList, ParameterManager& parameterManager) {
		size_t i = 0;
		auto it = parameters.begin();
		while (i < variables.Size) {
			Parameter* p = it->get();
			if (p->IsEmpty) {
				Parameter* global = parameterManager.Parameters.get(p->Name);
				if (!global) {
					auto text = std::format(_T("Parameter for variable '{}' is missing.\n"), p->Name);
					Logger::logOnce(LogType::WARNING, text.c_str(), i);
					i++;
					it++;
					continue;
				}
				p = global;
				if (p->IsEmpty) {
					auto text = std::format(_T("Parameter for variable '{}' is empty.\n"), p->Name);
					Logger::logOnce(LogType::WARNING, text.c_str(), i);
					i++;
					it++;
					continue;
				}
			}
			ConstantBufferField* v = variables[i];
			buffer.setValue(p->RawValue, v->size, v->offset);
			i++;
			it++;
		}
		buffer.set(commandList, bindSlot);
	}
}