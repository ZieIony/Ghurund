#pragma once

#include "ShaderConstant.h"

namespace Ghurund{
    class Sampler:public ShaderConstant {
    public:
        D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
        
        Sampler(const char *name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):ShaderConstant(name, bindPoint, visibility) {
        }

        void build() {
            samplerDesc.Filter = D3D12_FILTER_ANISOTROPIC;
            samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
            samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
            samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
            samplerDesc.MipLODBias = 0;
            samplerDesc.MaxAnisotropy = 16;
            samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
            samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
            samplerDesc.MinLOD = 0.0f;
            samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
            samplerDesc.ShaderRegister = 0;
            samplerDesc.RegisterSpace = 0;
            samplerDesc.ShaderVisibility = visibility;
        }
    };
}