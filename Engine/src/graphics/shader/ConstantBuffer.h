#pragma once

#include "collection/List.h"
#include "core/ScopedPointer.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/buffer/DynamicBuffer.h"
#include "graphics/shader/ConstantBufferField.h"
#include "graphics/shader/ShaderConstant.h"

namespace Ghurund {
    class ConstantBuffer:public ShaderConstant, public ParameterProvider {
    public:
        GPUBuffer buffer;
        Array<ConstantBufferField*> variables;
        PointerArray<Parameter*> parameters;
#ifdef _DEBUG
        bool* reported;
#endif

        ConstantBuffer(Graphics& graphics, ID3D12ShaderReflectionConstantBuffer* constantBuffer, D3D12_SHADER_BUFFER_DESC& bufferDesc, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):
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
                variables[i] = ghnew ConstantBufferField(variableDesc.Name, variableDesc.Size, variableDesc.StartOffset);
            }

            buffer.init(graphics, bufferDesc.Size);
        }

        ~ConstantBuffer() {
            for (size_t i = 0; i < variables.Size; i++)
                delete variables[i];
#ifdef _DEBUG
            delete[] reported;
#endif
        }

        virtual void initParameters(ParameterManager& parameterManager) override {
            for (size_t i = 0; i < variables.Size; i++) {
                ValueParameter* p = (ValueParameter*)parameterManager.getParameter(variables[i]->name);
                ScopedPointer<ValueParameter> vp = ghnew ValueParameter(variables[i]->name, p->ValueType);
                vp->DefaultValue = p->Value;
                parameters.set(i, vp);
            }
        }

        virtual void updateParameters() override {
            for (size_t i = 0; i < variables.Size; i++) {
                ValueParameter* p = (ValueParameter*)parameters[i];
#ifdef _DEBUG
                if (p->Value == nullptr) {
                    if (!reported[i]) {
                        Logger::log(LogType::WARNING, _T("Parameter for variable '%hs' is missing. Parameters are initialized only once and then reused. Please make sure that the parameter is available either in the parameter manager when the shader is initialized or in the shader when the shader is used.\n"), variables[i]->name);
                        reported[i] = true;
                    }
                    continue;
                }
#endif
                ConstantBufferField* v = variables[i];
                buffer.setValue(p->getValue(), v->size, v->offset);
            }
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        void set(Graphics& graphics, CommandList& commandList) {
            buffer.set(graphics, commandList, bindSlot);
        }
    };

}