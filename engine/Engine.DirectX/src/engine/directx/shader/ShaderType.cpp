#include "ghedxpch.h"
#include "ShaderType.h"

namespace Ghurund::Engine::DirectX {
    const ShaderType ShaderType::VERTEX = ShaderType(ShaderTypeEnum::VERTEX, "VERTEX", "vs", "vertexMain", D3D12_SHADER_VISIBILITY_VERTEX);
    const ShaderType ShaderType::PIXEL = ShaderType(ShaderTypeEnum::PIXEL, "PIXEL", "ps", "pixelMain", D3D12_SHADER_VISIBILITY_PIXEL);
    const ShaderType ShaderType::GEOMETRY = ShaderType(ShaderTypeEnum::GEOMETRY, "GEOMETRY", "gs", "geometryMain", D3D12_SHADER_VISIBILITY_GEOMETRY);
    const ShaderType ShaderType::HULL = ShaderType(ShaderTypeEnum::HULL, "HULL", "hs", "hullMain", D3D12_SHADER_VISIBILITY_HULL);
    const ShaderType ShaderType::D0MAIN = ShaderType(ShaderTypeEnum::D0MAIN, "D0MAIN", "ds", "domainMain", D3D12_SHADER_VISIBILITY_DOMAIN);
    const ShaderType ShaderType::COMPUTE = ShaderType(ShaderTypeEnum::COMPUTE, "COMPUTE", "cs", "computeMain", D3D12_SHADER_VISIBILITY_ALL);
}