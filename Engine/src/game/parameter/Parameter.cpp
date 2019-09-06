#include "Parameter.h"
#include "ParameterManager.h"

namespace Ghurund {
    const ParameterId ParameterId::VIEWPORT_SIZE = ParameterId(ParameterIdEnum::VIEWPORT_SIZE, _T("VIEWPORT_SIZE"), "viewportSize", ParameterType::FLOAT2);
    const ParameterId ParameterId::OUTLINE_COLOR = ParameterId(ParameterIdEnum::OUTLINE_COLOR, _T("OUTLINE_COLOR"), "outlineColor", ParameterType::COLOR);
    const ParameterId ParameterId::PARTY_COLOR = ParameterId(ParameterIdEnum::PARTY_COLOR, _T("PARTY_COLOR"), "partyColor", ParameterType::COLOR);
    const ParameterId ParameterId::RANDOM = ParameterId(ParameterIdEnum::RANDOM, _T("RANDOM"), "random", ParameterType::FLOAT);
    const ParameterId ParameterId::AMBIENT_LIGHT = ParameterId(ParameterIdEnum::AMBIENT_LIGHT, _T("AMBIENT_LIGHT"), "ambientLight", ParameterType::COLOR);
    const ParameterId ParameterId::POSITION = ParameterId(ParameterIdEnum::POSITION, _T("POSITION"), "position", ParameterType::FLOAT3);
    const ParameterId ParameterId::ROTATION = ParameterId(ParameterIdEnum::ROTATION, _T("ROTATION"), "rotation", ParameterType::FLOAT3);
    const ParameterId ParameterId::SCALE = ParameterId(ParameterIdEnum::SCALE, _T("SCALE"), "scale", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_DIRECTION = ParameterId(ParameterIdEnum::CAMERA_DIRECTION, _T("CAMERA_DIRECTION"), "cameraDirection", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_POSITION = ParameterId(ParameterIdEnum::CAMERA_POSITION, _T("CAMERA_POSITION"), "cameraPosition", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_TARGET = ParameterId(ParameterIdEnum::CAMERA_TARGET, _T("CAMERA_TARGET"), "cameraTarget", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_UP = ParameterId(ParameterIdEnum::CAMERA_UP, _T("CAMERA_UP"), "cameraUp", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_RIGHT = ParameterId(ParameterIdEnum::CAMERA_RIGHT, _T("CAMERA_RIGHT"), "cameraRight", ParameterType::FLOAT3);
    const ParameterId ParameterId::FOV = ParameterId(ParameterIdEnum::FOV, _T("FOV"), "fov", ParameterType::FLOAT);
    const ParameterId ParameterId::ZNEAR = ParameterId(ParameterIdEnum::ZNEAR, _T("ZNEAR"), "zNear", ParameterType::FLOAT);
    const ParameterId ParameterId::ZFAR = ParameterId(ParameterIdEnum::ZFAR, _T("ZFAR"), "zFar", ParameterType::FLOAT);
    const ParameterId ParameterId::WORLD = ParameterId(ParameterIdEnum::WORLD, _T("WORLD"), "world", ParameterType::MATRIX);
    const ParameterId ParameterId::WORLD_IT = ParameterId(ParameterIdEnum::WORLD_IT, _T("WORLD_IT"), "worldIT", ParameterType::MATRIX);
    const ParameterId ParameterId::VIEW = ParameterId(ParameterIdEnum::VIEW, _T("VIEW"), "view", ParameterType::MATRIX);
    const ParameterId ParameterId::PROJECTION = ParameterId(ParameterIdEnum::PROJECTION, _T("PROJECTION"), "projection", ParameterType::MATRIX);
    const ParameterId ParameterId::VIEW_PROJECTION = ParameterId(ParameterIdEnum::VIEW_PROJECTION, _T("VIEW_PROJECTION"), "viewProjection", ParameterType::MATRIX);
    const ParameterId ParameterId::VIEW_PROJECTION_INV = ParameterId(ParameterIdEnum::VIEW_PROJECTION_INV, _T("VIEW_PROJECTION_INV"), "viewProjectionInv", ParameterType::MATRIX);
    const ParameterId ParameterId::DIFFUSE_TEXTURE = ParameterId(ParameterIdEnum::DIFFUSE_TEXTURE, _T("DIFFUSE_TEXTURE"), "diffuseTexture", ParameterType::TEXTURE);
    const ParameterId ParameterId::SPECULAR_TEXTURE = ParameterId(ParameterIdEnum::SPECULAR_TEXTURE, _T("SPECULAR_TEXTURE"), "specularTexture", ParameterType::TEXTURE);
    const ParameterId ParameterId::NORMAL_TEXTURE = ParameterId(ParameterIdEnum::NORMAL_TEXTURE, _T("NORMAL_TEXTURE"), "normalTexture", ParameterType::TEXTURE);

    const EnumValues<ParameterIdEnum, ParameterId> ParameterId::VALUES = {
        &ParameterId::VIEWPORT_SIZE,
        &ParameterId::OUTLINE_COLOR,
        &ParameterId::PARTY_COLOR,
        &ParameterId::RANDOM,
        &ParameterId::AMBIENT_LIGHT,
        &ParameterId::POSITION,
        &ParameterId::SCALE,
        &ParameterId::CAMERA_DIRECTION,
        &ParameterId::CAMERA_POSITION,
        &ParameterId::CAMERA_TARGET,
        &ParameterId::CAMERA_UP,
        &ParameterId::CAMERA_RIGHT,
        &ParameterId::FOV,
        &ParameterId::ZNEAR,
        &ParameterId::ZFAR,
        &ParameterId::WORLD,
        &ParameterId::WORLD_IT,
        &ParameterId::VIEW,
        &ParameterId::PROJECTION,
        &ParameterId::VIEW_PROJECTION,
        &ParameterId::VIEW_PROJECTION_INV,
        &ParameterId::DIFFUSE_TEXTURE,
        &ParameterId::SPECULAR_TEXTURE,
        &ParameterId::NORMAL_TEXTURE
    };
}