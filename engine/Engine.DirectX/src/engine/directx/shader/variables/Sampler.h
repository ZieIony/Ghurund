#pragma once

#include "ShaderConstant.h"

#include "engine/graphics/texture/TextureFilter.h"

namespace Ghurund::Engine::DirectX {
    class Sampler:public ShaderConstant {
    private:
        D3D12_STATIC_SAMPLER_DESC samplerDesc = {};

    public:
        Sampler(const char* name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):ShaderConstant(name, bindPoint, visibility) {
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
            samplerDesc.ShaderRegister = bindPoint;
            samplerDesc.RegisterSpace = 0;
            samplerDesc.ShaderVisibility = visibility;
        }

        inline void setFilter(TextureFilter filter) {
            if (filter == TextureFilter::POINT) {
                samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
            } else if(filter == TextureFilter::LINEAR) {
                samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
            } else if(filter == TextureFilter::ANISOTROPIC) {
                samplerDesc.Filter = D3D12_FILTER_ANISOTROPIC;
            }
        }

        __declspec(property(put = setFilter)) TextureFilter Filter;

        inline D3D12_STATIC_SAMPLER_DESC get() const {
            return samplerDesc;
        }
    };
}