#include "ghpch.h"
#include "ResourceFormat.h"

namespace Ghurund {
    const ResourceFormat& ResourceFormat::ENTITY = ResourceFormat(nullptr, true, true);

    const ResourceFormat& ResourceFormat::SCENE = ResourceFormat(L"scene", true, true);

    const ResourceFormat& ResourceFormat::HLSL = ResourceFormat(L"hlsl", true, false);
    const ResourceFormat& ResourceFormat::SHADER = ResourceFormat(L"shader", true, true);

    const ResourceFormat& ResourceFormat::JPG = ResourceFormat(L"jpg", true, false);
    const ResourceFormat& ResourceFormat::JPEG = ResourceFormat(L"jpeg", true, false);
    const ResourceFormat& ResourceFormat::PNG = ResourceFormat(L"png", true, false);

    const ResourceFormat& ResourceFormat::SVG = ResourceFormat(L"svg", true, false);

    const ResourceFormat& ResourceFormat::MATERIAL = ResourceFormat(L"material", true, true);

    const ResourceFormat& ResourceFormat::MODEL = ResourceFormat(L"model", true, true);

    const ResourceFormat& ResourceFormat::MESH = ResourceFormat(L"mesh", true, true);
    const ResourceFormat& ResourceFormat::OBJ = ResourceFormat(L"obj", true, true);

    const ResourceFormat& ResourceFormat::WAV = ResourceFormat(L"wav", true, false);

    const ResourceFormat& ResourceFormat::SCRIPT = ResourceFormat(L"script", true, true);

    const ResourceFormat* ResourceFormat::values[14] = {
        &ResourceFormat::ENTITY,
        &ResourceFormat::SCENE,
        &ResourceFormat::HLSL,
        &ResourceFormat::SHADER,
        &ResourceFormat::JPG,
        &ResourceFormat::JPEG,
        &ResourceFormat::PNG,
        &ResourceFormat::SVG,
        &ResourceFormat::MATERIAL,
        &ResourceFormat::MODEL,
        &ResourceFormat::MESH,
        &ResourceFormat::OBJ,
        &ResourceFormat::WAV,
        &ResourceFormat::SCRIPT
    };
}