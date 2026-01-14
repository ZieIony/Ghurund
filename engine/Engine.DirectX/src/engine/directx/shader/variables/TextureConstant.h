#pragma once

#include "ShaderConstant.h"

namespace Ghurund::Engine::DirectX {
    class DxTextureConstantInfo:public ShaderConstant {
    public:
        DxTextureConstantInfo(
            const char *name,
            unsigned int bindPoint,
            D3D12_SHADER_VISIBILITY visibility
        ):ShaderConstant(name, bindPoint, visibility) {
        }
    };
}