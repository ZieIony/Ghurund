#include "ghedxpch.h"
#include "DxShaderType.h"

namespace Ghurund::Engine::DirectX {
    const DxShaderType DxShaderType::VERTEX = DxShaderType(DxShaderTypeEnum::VERTEX, "VERTEX", "vs", "vertexMain", D3D12_SHADER_VISIBILITY_VERTEX);
    const DxShaderType DxShaderType::PIXEL = DxShaderType(DxShaderTypeEnum::PIXEL, "PIXEL", "ps", "pixelMain", D3D12_SHADER_VISIBILITY_PIXEL);
    const DxShaderType DxShaderType::GEOMETRY = DxShaderType(DxShaderTypeEnum::GEOMETRY, "GEOMETRY", "gs", "geometryMain", D3D12_SHADER_VISIBILITY_GEOMETRY);
    const DxShaderType DxShaderType::HULL = DxShaderType(DxShaderTypeEnum::HULL, "HULL", "hs", "hullMain", D3D12_SHADER_VISIBILITY_HULL);
    const DxShaderType DxShaderType::D0MAIN = DxShaderType(DxShaderTypeEnum::D0MAIN, "D0MAIN", "ds", "domainMain", D3D12_SHADER_VISIBILITY_DOMAIN);
    const DxShaderType DxShaderType::COMPUTE = DxShaderType(DxShaderTypeEnum::COMPUTE, "COMPUTE", "cs", "computeMain", D3D12_SHADER_VISIBILITY_ALL);
}