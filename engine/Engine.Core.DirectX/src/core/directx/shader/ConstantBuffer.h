#pragma once

#include "core/collection/PointerArray.h"
#include "core/SharedPointer.h"
//#include "core/directx/shader/parameter/Parameter.h"
#include "core/directx/buffer/DynamicBuffer.h"
#include "core/directx/shader/ConstantBufferField.h"
#include "core/directx/shader/ShaderConstant.h"

#include <d3dcompiler.h>

namespace Ghurund::Core::DirectX {
    class ConstantBuffer:public ShaderConstant {
    public:
        GPUBuffer buffer;
        Array<ConstantBufferField*> variables;
        //PointerArray<Parameter*> parameters;
#ifdef _DEBUG
        bool* reported;
#endif

        ConstantBuffer(Graphics& graphics, ID3D12ShaderReflectionConstantBuffer* constantBuffer, D3D12_SHADER_BUFFER_DESC& bufferDesc, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility);

        ~ConstantBuffer() {
            variables.deleteItems();
#ifdef _DEBUG
            delete[] reported;
#endif
        }

        /*(virtual void initParameters(ParameterManager& parameterManager) override;

        virtual void updateParameters() override;

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }*/

        void set(Graphics& graphics, CommandList& commandList) {
            buffer.set(graphics, commandList, bindSlot);
        }
    };

}