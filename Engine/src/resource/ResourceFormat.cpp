#include "ResourceFormat.h"

namespace Ghurund {
    const ResourceFormat &ResourceFormat::AUTO = ResourceFormat(0, nullptr, true, true);
    const ResourceFormat &ResourceFormat::ENTITY = ResourceFormat(0, nullptr, true, true);
    const ResourceFormat &ResourceFormat::HLSL = ResourceFormat(1, _T("hlsl"), true, false);
    const ResourceFormat &ResourceFormat::SHADER = ResourceFormat(2, _T("shader"), true, true);
    const ResourceFormat &ResourceFormat::JPG = ResourceFormat(1, _T("jpg"), true, false);
    const ResourceFormat &ResourceFormat::JPEG = ResourceFormat(2, _T("jpeg"), true, false);
    const ResourceFormat &ResourceFormat::MATERIAL = ResourceFormat(1, _T("material"), true, false);

    const Array<const ResourceFormat*> ResourceFormat::values = {&ResourceFormat::AUTO, &ResourceFormat::HLSL, &ResourceFormat::SHADER, &ResourceFormat::JPG, &ResourceFormat::JPEG, &ResourceFormat::MATERIAL};
}