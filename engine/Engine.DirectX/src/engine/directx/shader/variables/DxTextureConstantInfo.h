#pragma once

#include "DxShaderConstantInfo.h"

namespace Ghurund::Engine::DirectX {
    class DxTextureConstantInfo:public DxShaderConstantInfo {
    public:
        D3D_SRV_DIMENSION dimension;

        DxTextureConstantInfo(
            const char *name,
            unsigned int bindPoint,
            D3D12_SHADER_VISIBILITY visibility,
            D3D_SRV_DIMENSION dimension
        ):DxShaderConstantInfo(name, bindPoint, visibility), dimension(dimension) {
        }
    };
}
