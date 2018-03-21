#pragma once

#include "ShaderConstant.h"

namespace Ghurund {
    class TextureConstant:public ShaderConstant {
    public:
        TextureConstant(const char *name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):ShaderConstant(name, bindPoint, visibility) {}
    };
}