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

        ConstantBuffer(Graphics& graphics, ID3D12ShaderReflectionConstantBuffer* constantBuffer, D3D12_SHADER_BUFFER_DESC& bufferDesc, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility);

        ~ConstantBuffer() {
            variables.deleteItems();
#ifdef _DEBUG
            delete[] reported;
#endif
        }

        virtual void initParameters(ParameterManager& parameterManager) override;

        virtual void updateParameters() override;

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        void set(Graphics& graphics, CommandList& commandList) {
            buffer.set(graphics, commandList, bindSlot);
        }
    };

}