#include "ResourceFormat.h"

namespace Ghurund {
    const ResourceFormat &ResourceFormat::AUTO = ResourceFormat(0, nullptr, true, true);
    const ResourceFormat &ResourceFormat::ENTITY = ResourceFormat(0, nullptr, true, true);
    const ResourceFormat &ResourceFormat::HLSL = ResourceFormat(1, "hlsl", true, false);
    const ResourceFormat &ResourceFormat::SHADER = ResourceFormat(2, "shader", true, true);
    const ResourceFormat &ResourceFormat::JPG = ResourceFormat(1, "jpg", true, false);
    const ResourceFormat &ResourceFormat::MATERIAL = ResourceFormat(1, "material", true, false);

    const ResourceFormat ResourceFormat::values[] = {ResourceFormat::AUTO, ResourceFormat::HLSL, ResourceFormat::SHADER, ResourceFormat::JPG, ResourceFormat::MATERIAL};
}