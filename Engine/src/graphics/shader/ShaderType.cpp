#include "ShaderType.h"

namespace Ghurund {
    const ShaderType &ShaderType::VS = ShaderType(1, "vs", "vertexMain", D3D12_SHADER_VISIBILITY_VERTEX);
    const ShaderType &ShaderType::PS = ShaderType(2, "ps", "pixelMain", D3D12_SHADER_VISIBILITY_PIXEL);
    const ShaderType &ShaderType::GS = ShaderType(4, "gs", "geometryMain", D3D12_SHADER_VISIBILITY_GEOMETRY);
    const ShaderType &ShaderType::HS = ShaderType(8, "hs", "hullMain", D3D12_SHADER_VISIBILITY_HULL);
    const ShaderType &ShaderType::DS = ShaderType(16, "ds", "domainMain", D3D12_SHADER_VISIBILITY_DOMAIN);
    const ShaderType &ShaderType::CS = ShaderType(32, "cs", "computeMain", D3D12_SHADER_VISIBILITY_ALL);

    const ShaderType ShaderType::values[] = {ShaderType::VS, ShaderType::PS, ShaderType::GS, ShaderType::HS, ShaderType::DS, ShaderType::CS};
}