#include "ResourceFormat.h"

namespace Ghurund {
    const ResourceFormat &ResourceFormat::ENTITY = ResourceFormat(nullptr, true, true);

    const ResourceFormat &ResourceFormat::SCENE = ResourceFormat(_T("scene"), true, true);

    const ResourceFormat &ResourceFormat::HLSL = ResourceFormat(_T("hlsl"), true, false);
    const ResourceFormat &ResourceFormat::SHADER = ResourceFormat(_T("shader"), true, true);

    const ResourceFormat &ResourceFormat::JPG = ResourceFormat(_T("jpg"), true, false);
    const ResourceFormat &ResourceFormat::JPEG = ResourceFormat(_T("jpeg"), true, false);
    const ResourceFormat &ResourceFormat::PNG = ResourceFormat(_T("png"), true, false);

    const ResourceFormat &ResourceFormat::MATERIAL = ResourceFormat(_T("material"), true, true);

    const ResourceFormat &ResourceFormat::MODEL = ResourceFormat(_T("model"), true, true);

    const ResourceFormat &ResourceFormat::MESH = ResourceFormat(_T("mesh"), true, true);
    const ResourceFormat &ResourceFormat::OBJ = ResourceFormat(_T("obj"), true, true);

    const ResourceFormat &ResourceFormat::WAV = ResourceFormat(_T("wav"), true, false);

    const ResourceFormat &ResourceFormat::SCRIPT = ResourceFormat(_T("script"), true, true);

    const ResourceFormat* ResourceFormat::values[13] = {
        &ResourceFormat::ENTITY,
        &ResourceFormat::SCENE,
        &ResourceFormat::HLSL,
        &ResourceFormat::SHADER,
        &ResourceFormat::JPG,
        &ResourceFormat::JPEG,
        &ResourceFormat::PNG,
        &ResourceFormat::MATERIAL,
        &ResourceFormat::MODEL,
        &ResourceFormat::MESH,
        &ResourceFormat::OBJ,
        &ResourceFormat::WAV,
        &ResourceFormat::SCRIPT
    };
}