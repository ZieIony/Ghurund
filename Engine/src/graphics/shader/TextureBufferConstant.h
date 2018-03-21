#pragma once

#include "ShaderConstant.h"

namespace Ghurund {
    class TextureBufferConstant:public ShaderConstant {
    public:
        TextureBufferConstant(ID3D12ShaderReflectionConstantBuffer *constantBuffer, D3D12_SHADER_BUFFER_DESC &bufferDesc, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):ShaderConstant(bufferDesc.Name, bindPoint, visibility) {}
    };
}