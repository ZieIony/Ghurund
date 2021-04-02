#include "ghpch.h"
#include "ConstantBuffer.h"
#include "game/parameter/ValueParameter.h"

namespace Ghurund {
    ConstantBuffer::ConstantBuffer(Graphics& graphics, ID3D12ShaderReflectionConstantBuffer* constantBuffer, D3D12_SHADER_BUFFER_DESC& bufferDesc, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility) :
        ShaderConstant(bufferDesc.Name, bindPoint, visibility),
        parameters(PointerArray<Parameter*>(bufferDesc.Variables)),
        variables(Array<ConstantBufferField*>(bufferDesc.Variables)) {

#ifdef _DEBUG
        reported = ghnew bool[variables.Size];
#endif

        for (unsigned int i = 0; i < variables.Size; i++) {
            parameters.set(i, nullptr);
#ifdef _DEBUG
            reported[i] = false;
#endif
            ID3D12ShaderReflectionVariable* variable = constantBuffer->GetVariableByIndex(i);
            D3D12_SHADER_VARIABLE_DESC variableDesc;
            variable->GetDesc(&variableDesc);
            variables.set(i, ghnew ConstantBufferField(variableDesc.Name, variableDesc.Size, variableDesc.StartOffset));
        }

        buffer.init(graphics, bufferDesc.Size);
    }
    
    void ConstantBuffer::initParameters(ParameterManager& parameterManager) {
        for (size_t i = 0; i < variables.Size; i++) {
            ConstantBufferField* variable = variables[i];
            ValueParameter* vp = ghnew ValueParameter(variable->name.Data, ParameterType::fromSize(variable->size));
            ValueParameter* p = (ValueParameter*)parameterManager.getParameter(variable->name);
            if (p)
                vp->DefaultValue = p->Value;
            parameters.set(i, vp);
            vp->release();
        }
    }
    
    void ConstantBuffer::updateParameters() {
        for (size_t i = 0; i < variables.Size; i++) {
            ValueParameter* p = (ValueParameter*)parameters[i];
#ifdef _DEBUG
            if (p->Value == nullptr) {
                if (!reported[i]) {
                    Logger::log(LogType::WARNING, _T("Parameter for variable '%hs' is missing.\n"), variables[i]->name);
                    reported[i] = true;
                }
                continue;
            }
#endif
            ConstantBufferField* v = variables[i];
            buffer.setValue(p->getValue(), v->size, v->offset);
        }
    }
}