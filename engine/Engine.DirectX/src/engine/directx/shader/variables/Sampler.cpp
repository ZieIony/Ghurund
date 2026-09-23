#include "ghedxpch.h"
#include "Sampler.h"

namespace Ghurund::Engine::DirectX {
    Sampler::Sampler(const char* name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):ShaderConstant(name, bindPoint, visibility) {
        samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
        samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
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
}
