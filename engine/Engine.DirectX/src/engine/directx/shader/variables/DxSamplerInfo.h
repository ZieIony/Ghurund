#pragma once

#include "DxShaderConstantInfo.h"

#include "engine/graphics/texture/TextureFilter.h"

namespace Ghurund::Engine::DirectX {
    class DxSamplerInfo:public DxShaderConstantInfo {
    private:
        D3D12_STATIC_SAMPLER_DESC samplerDesc = {};

    public:
        DxSamplerInfo(const char* name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility);

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
