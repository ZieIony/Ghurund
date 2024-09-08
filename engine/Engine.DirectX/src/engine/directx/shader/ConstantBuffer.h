#pragma once

#include "core/IntrusivePointer.h"
//#include "engine/directx/shader/parameter/Parameter.h"
#include "engine/directx/buffer/DynamicBuffer.h"
#include "engine/directx/shader/ConstantBufferField.h"
#include "engine/directx/shader/ShaderConstant.h"

#include <d3dcompiler.h>

namespace Ghurund::Engine::DirectX {
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