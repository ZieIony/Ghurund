#include "ShaderType.h"

namespace Ghurund {
    const ShaderType VS = ShaderType(1, "vs", "vertexMain");
    const ShaderType PS = ShaderType(2, "ps", "pixelMain");
    const ShaderType GS = ShaderType(4, "gs", "geometryMain");
    const ShaderType HS = ShaderType(8, "hs", "hullMain");
    const ShaderType DS = ShaderType(16, "ds", "domainMain");
    const ShaderType CS = ShaderType(32, "cs", "computeMain");
    const ShaderType *values = {VS, PS, GS, HS, DS, CS};

    const ShaderType *ShaderType::getValues() {
        return values;
    }
}