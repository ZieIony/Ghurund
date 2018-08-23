#pragma once

#include "ShaderVariable.h"
#include "ShaderConstant.h"
#include "graphics/buffer/DynamicBuffer.h"
#include "collection/List.h"
#include "game/ParameterManager.h"

namespace Ghurund {
    class ConstantBuffer:public ShaderConstant {
    public:
		DynamicBuffer buffer;
		size_t variableCount;
        ShaderVariable **variables;
        Parameter **managerParameters;
        Parameter **parameters;
#ifdef _DEBUG
		bool *reported;
#endif

        ConstantBuffer(Graphics &graphics, ID3D12ShaderReflectionConstantBuffer *constantBuffer, D3D12_SHADER_BUFFER_DESC &bufferDesc, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):
            ShaderConstant(bufferDesc.Name, bindPoint, visibility) {

            variableCount = bufferDesc.Variables;

            variables = ghnew ShaderVariable*[variableCount];
#ifdef _DEBUG
			reported = ghnew bool[variableCount];
#endif
			for(unsigned int i = 0; i<variableCount; i++) {
#ifdef _DEBUG
				reported[i] = false;
#endif
				ID3D12ShaderReflectionVariable *variable = constantBuffer->GetVariableByIndex(i);
                D3D12_SHADER_VARIABLE_DESC variableDesc;
                variable->GetDesc(&variableDesc);
                variables[i] = ghnew ShaderVariable(variableDesc.Name, variableDesc.Size, variableDesc.StartOffset);
            }
			buffer.init(graphics, bufferDesc.Size);
		}

        ~ConstantBuffer() {
            for(size_t i = 0; i<variableCount; i++) {
                delete variables[i];
                delete parameters[i];
            }
            delete[] variables;
            delete[] parameters;
            delete[] managerParameters;
#ifdef _DEBUG
			delete[] reported;
#endif
		}

        void initParameters(ParameterManager &parameterManager) {
            managerParameters = ghnew Parameter*[variableCount];
            parameters = ghnew Parameter*[variableCount];
            for(size_t i = 0; i<variableCount; i++) {
                ShaderVariable *v = variables[i];
                managerParameters[i] = parameterManager.get(v->name);
                parameters[i] = nullptr;
            }
        }

        /*Parameter *getParameter(size_t i) {
            return parameters[i];
        }

        Parameter *getParameter(const ASCIIString &name) {
            return nullptr;// parameters[i];
        }

        void setParameter(size_t i, const void *value) {
        }

        void setParameter(const ASCIIString &name, const void *value) {
        }*/

        size_t getParameterCount() {
            return variableCount;
        }

        void set(CommandList &commandList, ParameterManager &parameterManager) {
            for(size_t i = 0; i<variableCount; i++) {
                Parameter *p = parameters[i];
                if(p==nullptr)
                    p = managerParameters[i];
				if (p == nullptr) {
#ifdef _DEBUG
					if (!reported[i]) {
                        ShaderVariable *v = variables[i];
                        p = managerParameters[i] = parameterManager.get(v->name);
                        if(p == nullptr) {
                            Logger::log(_T("Parameter for variable '%hs' is missing\n"), variables[i]->name);
                            reported[i] = true;
                        }
					}
#endif
					continue;
				}
                ShaderVariable *v = variables[i];
                buffer.setValue(p->getValue(), v->size, v->offset);
            }
            buffer.set(commandList, bindSlot);
        }
    };

}